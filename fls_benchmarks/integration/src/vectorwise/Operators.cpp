#include "vectorwise/Operators.hpp"
#include "benchmarks/fls/config.hpp"
#include "common/Compat.hpp"
#include "common/runtime/Concurrency.hpp"
#include "common/runtime/SIMD.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <x86intrin.h>

namespace vectorwise {

using runtime::barrier;

size_t Select::next() {
	while (true) {
		auto n = child->next();
		if (n == EndOfStream) return EndOfStream;
		n = condition->evaluate(n);
		if (n > 0) return n;
	}
}

size_t Project::next() {
	auto n = child->next();
	if (n == EndOfStream) return EndOfStream;
	for (auto& expression : expressions)
		expression->evaluate(n);
	return n;
}

size_t FixedAggr::next() {
	if (!consumed) {
		size_t found = 0;
		for (auto n = child->next(); n != EndOfStream; n = child->next()) {
			found = aggregates.evaluate(n);
		}
		consumed = true;
		return found;
	} else {
		return EndOfStream;
	}
}

Scan::Scan(Shared& s, size_t ttl_tup_c, size_t vec_c)
    : shared(s)
    , needsInit(true)
    , currentChunk(0)
    , lastOffset(0)
    , ttl_tup_c(ttl_tup_c)
    , vec_c(vec_c) {
	scan_chunk_c         = 1;
	size_t scan_morsel_c = cfg::scan_morsel_c;
	if (vec_c < scan_morsel_c) { scan_chunk_c = scan_morsel_c / vec_c + 1; }
	vecInChunk = scan_chunk_c;
}

// FLS_CHANGE
void Scan::addConsumer(void** col_p, size_t type_sz) {
	if (cfg::is_bitpacked) {
		// bitpacked
		consumers.emplace_back(col_p, (vec_c * type_sz) / 8);
	} else {
		// non-bitpacked
		consumers.emplace_back(col_p, (vec_c * type_sz));
	}
}

size_t Scan::next() {
	auto step = 1;

	if (vecInChunk == scan_chunk_c) {
		auto prevChunk = currentChunk;
		currentChunk   = shared.pos.fetch_add(1);
		auto chunkSkip = currentChunk - prevChunk;
		if (needsInit) {
			step      = chunkSkip * scan_chunk_c;
			needsInit = false;
		} else {
			chunkSkip -= 1;
			step = chunkSkip * scan_chunk_c + 1;
		}
		vecInChunk = 0;
	}

	auto nextBegin = lastOffset + step * vec_c;
	if (nextBegin >= ttl_tup_c) return EndOfStream;
	auto nextBatchSize = std::min(ttl_tup_c - nextBegin, vec_c);
	for (auto& cons : consumers)
		*cons.first = (void*)(*(uint8_t**)cons.first + step * cons.second);
	lastOffset = nextBegin;
	vecInChunk++;
	return nextBatchSize;
}

ResultWriter::Input::Input(void* d, size_t size, runtime::BlockRelation::Attribute attr)
    : data(d)
    , elementSize(size)
    , attribute(attr) {}

ResultWriter::ResultWriter(Shared& s)
    : shared(s)
    , currentBlock(nullptr, nullptr) {}

size_t ResultWriter::next() {
	size_t found = 0;
	for (pos_t n = child->next(); n != EndOfStream; n = child->next()) {
		found += n;
		// assure that enough space is available in current block to fit result of
		// all buffers
		if (currentBlock.spaceRemaining() < n) currentBlock = shared.result->result->createBlock(n);
		auto blockSize = currentBlock.size();
		for (const auto& input : inputs)
			// copy data from intermediate buffers into result relation
			std::memcpy(addBytes(currentBlock.data(input.attribute), input.elementSize * blockSize),
			            input.data,
			            n * input.elementSize);
		// update result relation size
		currentBlock.addedElements(n);
	}
	return found;
}

pos_t Hashjoin::joinAll() {
	size_t found = 0;
	// perform continuation
	for (auto entry = cont.buildMatch; entry != shared.ht.end(); entry = entry->next) {
		if (entry->hash == cont.probeHash) {
			buildMatches[found]   = entry;
			probeMatches[found++] = cont.nextProbe;
			if (found == batchSize) {
				// output buffers are full, save state for continuation
				cont.buildMatch = entry->next;
				return batchSize;
			}
		}
	}
	if (cont.buildMatch != shared.ht.end()) cont.nextProbe++;
	for (size_t i = cont.nextProbe, end = cont.numProbes; i < end; ++i) {
		auto hash = probeHashes[i];
		for (auto entry = shared.ht.find_chain_tagged(hash); entry != shared.ht.end(); entry = entry->next) {
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = i;
				if (found == batchSize && (entry->next || i + 1 < end)) {
					// output buffers are full, save state for continuation
					cont.buildMatch = entry->next;
					cont.probeHash  = hash;
					cont.nextProbe  = i;
					return batchSize;
				}
			}
		}
	}
	cont.buildMatch = shared.ht.end();
	cont.nextProbe  = cont.numProbes;
	return found;
}

pos_t Hashjoin::joinAllParallel() {
	size_t found         = 0;
	auto   followup      = contCon.followup;
	auto   followupWrite = contCon.followupWrite;

	if (followup == followupWrite) {
		for (size_t i = 0, end = cont.numProbes; i < end; ++i) {
			auto hash  = probeHashes[i];
			auto entry = shared.ht.find_chain_tagged(hash);
			if (entry != shared.ht.end()) {
				if (entry->hash == hash) {
					buildMatches[found] = entry;
					probeMatches[found] = i;
					found += 1;
				}
				if (entry->next != shared.ht.end()) {
					followupIds[followupWrite]     = i;
					followupEntries[followupWrite] = entry->next;
					followupWrite += 1;
				}
			}
		}
	}

	followupWrite %= followupBufferSize;

	while (followup != followupWrite) {
		auto remainingSpace = batchSize - found;
		auto nrFollowups =
		    followup <= followupWrite ? followupWrite - followup : followupBufferSize - (followup - followupWrite);
		// std::cout << "nrFollowups: " << nrFollowups << "\n";
		auto fittingElements = std::min((size_t)nrFollowups, remainingSpace);
		for (size_t j = 0; j < fittingElements; ++j) {
			size_t i     = followupIds[followup];
			auto   entry = followupEntries[followup];
			// followup = (followup + 1) % followupBufferSize;
			followup = (followup + 1);
			if (followup == followupBufferSize) followup = 0;
			auto hash = probeHashes[i];
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = i;
			}
			if (entry->next != shared.ht.end()) {
				followupIds[followupWrite]     = i;
				followupEntries[followupWrite] = entry->next;
				followupWrite                  = (followupWrite + 1) % followupBufferSize;
			}
		}
		if (fittingElements < nrFollowups) {
			// continuation
			contCon.followupWrite = followupWrite;
			contCon.followup      = followup;
			return found;
		}
	}
	cont.nextProbe        = cont.numProbes;
	contCon.followup      = 0;
	contCon.followupWrite = 0;
	return found;
}

pos_t Hashjoin::joinAllSIMD() {
	size_t found         = 0;
	auto   followup      = contCon.followup;
	auto   followupWrite = contCon.followupWrite;

	if (followup == followupWrite) {

#ifdef __AVX512F__ // if AVX 512 available, use it!
#if HASH_SIZE == 32
		size_t rest = cont.numProbes % 8;
		auto   ids  = _mm512_set_epi32(0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0);
		for (size_t i = 0, end = cont.numProbes - rest; i < end; i += 8) {

			// load hashes
			// auto hash = probeHashes[i];
			// Vec8u hashes(probeHashes + i);
			auto  hashDense = _mm256_loadu_si256((const __m256i*)(probeHashes + i));
			Vec8u hashes    = _mm512_cvtepu32_epi64(hashDense);
			// find entry pointers in ht
			Vec8uM entries = shared.ht.find_chain_tagged(hashes);
			// load entry hashes
			auto entryHashes =
			    _mm512_mask_i64gather_epi32(hashDense,
			                                entries.mask,
			                                entries.vec + Vec8u(offsetof(decltype(shared.ht)::EntryHeader, hash)),
			                                nullptr,
			                                1);
			{
				// Check if hashes match
				__mmask8 hashesEq = _mm512_mask_cmpeq_epi32_mask(
				    entries.mask, _mm512_castsi256_si512(entryHashes), _mm512_castsi256_si512(hashDense));
				// write pointers
				_mm512_mask_compressstoreu_epi64(buildMatches + found, hashesEq, entries.vec);
				static_assert(sizeof(pos_t) == 4,
				              "SIMD join assumes sizeof(pos_t) is 4"); // change the
				                                                       // types for
				                                                       // probeSels
				                                                       // if this
				                                                       // fails
				// write selection
				_mm512_mask_compressstoreu_epi32(probeMatches + found, hashesEq, ids);
				found += __builtin_popcount(hashesEq);
			}

			{
				// write continuations
				static_assert(offsetof(decltype(shared.ht)::EntryHeader, next) == 0,
				              "Hash is expected to be in first position");
				Vec8u    nextPtrs = _mm512_mask_i64gather_epi64(entries.vec, entries.mask, entries.vec, nullptr, 1);
				__mmask8 hasNext =
				    _mm512_mask_cmpneq_epi64_mask(entries.mask, nextPtrs, Vec8u(uint64_t(shared.ht.end())));
				if (hasNext) {
					// write pointers
					_mm512_mask_compressstoreu_epi64(followupEntries + followupWrite, hasNext, nextPtrs);
					static_assert(sizeof(pos_t) == 4,
					              "SIMD join assumes sizeof(pos_t) is 4"); // change the types
					                                                       // for probeSels if
					                                                       // this fails
					// write selection
					_mm512_mask_compressstoreu_epi32(followupIds + followupWrite, hasNext, ids);
					followupWrite += __builtin_popcount(hasNext);
				}
				ids = _mm512_add_epi32(ids, _mm512_set1_epi32(8));
			}
		}
#else
		size_t rest = cont.numProbes % 8;
		// auto ids = _mm256_set_epi32(7,6,5,4,3,2,1,0);
		auto ids = _mm512_set_epi32(0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0);
		for (size_t i = 0, end = cont.numProbes - rest; i < end; i += 8) {

			// load hashes
			// auto hash = probeHashes[i];
			Vec8u hashes(probeHashes + i);
			// find entry pointers in ht
			Vec8uM entries = shared.ht.find_chain_tagged(hashes);
			// load entry hashes
			Vec8u entryHashes =
			    _mm512_mask_i64gather_epi64(entries.vec,
			                                entries.mask,
			                                entries.vec + Vec8u(offsetof(decltype(shared.ht)::EntryHeader, hash)),
			                                nullptr,
			                                1);
			{
				// Check if hashes match
				__mmask8 hashesEq = _mm512_mask_cmpeq_epi64_mask(entries.mask, entryHashes, hashes);
				// write pointers
				_mm512_mask_compressstoreu_epi64(buildMatches + found, hashesEq, entries.vec);
				static_assert(sizeof(pos_t) == 4,
				              "SIMD join assumes sizeof(pos_t) is 4"); // change the
				                                                       // types for
				                                                       // probeSels
				                                                       // if this
				                                                       // fails
				// write selection
				_mm512_mask_compressstoreu_epi32(probeMatches + found, hashesEq, ids);
				found += __builtin_popcount(hashesEq);
			}

			{
				// write continuations
				static_assert(offsetof(decltype(shared.ht)::EntryHeader, next) == 0,
				              "Hash is expected to be in first position");
				Vec8u    nextPtrs = _mm512_mask_i64gather_epi64(entries.vec, entries.mask, entries.vec, nullptr, 1);
				__mmask8 hasNext =
				    _mm512_mask_cmpneq_epi64_mask(entries.mask, nextPtrs, Vec8u(uint64_t(shared.ht.end())));
				if (hasNext) {
					// write pointers
					_mm512_mask_compressstoreu_epi64(followupEntries + followupWrite, hasNext, nextPtrs);
					static_assert(sizeof(pos_t) == 4,
					              "SIMD join assumes sizeof(pos_t) is 4"); // change the types
					                                                       // for probeSels if
					                                                       // this fails
					// write selection
					_mm512_mask_compressstoreu_epi32(followupIds + followupWrite, hasNext, ids);
					followupWrite += __builtin_popcount(hasNext);
				}
				ids = _mm512_add_epi32(ids, _mm512_set1_epi32(8));
			}
		}
#endif // hash size
#else
		const size_t rest = cont.numProbes;
#endif
		for (size_t i = cont.numProbes - rest, end = cont.numProbes; i < end; ++i) {
			auto hash  = probeHashes[i];
			auto entry = shared.ht.find_chain_tagged(hash);
			if (entry != shared.ht.end()) {
				if (entry->hash == hash) {
					buildMatches[found] = entry;
					probeMatches[found] = i;
					found += 1;
				}
				if (entry->next != shared.ht.end()) {
					followupIds[followupWrite]     = i;
					followupEntries[followupWrite] = entry->next;
					followupWrite += 1;
				}
			}
		}
	}

	followupWrite %= followupBufferSize;

	while (followup != followupWrite) {
		auto remainingSpace = batchSize - found;
		auto nrFollowups =
		    followup <= followupWrite ? followupWrite - followup : followupBufferSize - (followup - followupWrite);
		auto fittingElements = std::min((size_t)nrFollowups, remainingSpace);
		for (size_t j = 0; j < fittingElements; ++j) {
			size_t i     = followupIds[followup];
			auto   entry = followupEntries[followup];
			followup     = (followup + 1);
			if (followup == followupBufferSize) followup = 0;
			auto hash = probeHashes[i];
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = i;
			}
			if (entry->next != shared.ht.end()) {
				followupIds[followupWrite]     = i;
				followupEntries[followupWrite] = entry->next;
				followupWrite                  = (followupWrite + 1) % followupBufferSize;
			}
		}
		if (fittingElements < nrFollowups) {
			// continuation
			contCon.followupWrite = followupWrite;
			contCon.followup      = followup;
			return found;
		}
	}
	cont.nextProbe        = cont.numProbes;
	contCon.followup      = 0;
	contCon.followupWrite = 0;
	return found;
}

pos_t Hashjoin::joinSel() {
	size_t found = 0;
	// perform continuation
	for (auto entry = cont.buildMatch; entry != shared.ht.end(); entry = entry->next) {
		if (entry->hash == cont.probeHash) {
			buildMatches[found]   = entry;
			probeMatches[found++] = probeSel[cont.nextProbe];
			if (found == batchSize) {
				// output buffers are full, save state for continuation
				cont.buildMatch = entry->next;
				return batchSize;
			}
		}
	}
	if (cont.buildMatch != shared.ht.end()) cont.nextProbe++;
	for (size_t i = cont.nextProbe, end = cont.numProbes; i < end; ++i) {
		auto hash = probeHashes[i];
		for (auto entry = shared.ht.find_chain_tagged(hash); entry != shared.ht.end(); entry = entry->next) {
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = probeSel[i];
				if (found == batchSize && (entry->next || i + 1 < end)) {
					// output buffers are full, save state for continuation
					cont.buildMatch = entry->next;
					cont.probeHash  = hash;
					cont.nextProbe  = i;
					return batchSize;
				}
			}
		}
	}
	cont.buildMatch = shared.ht.end();
	cont.nextProbe  = cont.numProbes;
	return found;
}

pos_t Hashjoin::joinSelParallel() {
	size_t found         = 0;
	auto   followup      = contCon.followup;
	auto   followupWrite = contCon.followupWrite;

	if (followup == followupWrite) {
		for (size_t i = 0, end = cont.numProbes; i < end; ++i) {
			auto hash  = probeHashes[i];
			auto entry = shared.ht.find_chain_tagged(hash);
			if (entry != shared.ht.end()) {
				if (entry->hash == hash) {
					buildMatches[found] = entry;
					probeMatches[found] = probeSel[i];
					found += 1;
				}
				if (entry->next != shared.ht.end()) {
					followupIds[followupWrite]     = i;
					followupEntries[followupWrite] = entry->next;
					followupWrite += 1;
				}
			}
		}
	}

	followupWrite %= followupBufferSize;

	while (followup != followupWrite) {
		auto remainingSpace = batchSize - found;
		auto nrFollowups =
		    followup <= followupWrite ? followupWrite - followup : followupBufferSize - (followup - followupWrite);
		auto fittingElements = std::min((size_t)nrFollowups, remainingSpace);
		for (size_t j = 0; j < fittingElements; ++j) {
			size_t i     = followupIds[followup];
			auto   entry = followupEntries[followup];
			followup     = (followup + 1) % followupBufferSize;
			auto hash    = probeHashes[i];
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = probeSel[i];
			}
			if (entry->next != shared.ht.end()) {
				followupIds[followupWrite]     = i;
				followupEntries[followupWrite] = entry->next;
				followupWrite                  = (followupWrite + 1) % followupBufferSize;
			}
		}
		if (fittingElements < nrFollowups) {
			// continuation
			contCon.followupWrite = followupWrite;
			contCon.followup      = followup;
			return found;
		}
	}
	cont.nextProbe        = cont.numProbes;
	contCon.followup      = 0;
	contCon.followupWrite = 0;
	return found;
}

pos_t Hashjoin::joinSelSIMD() {
	size_t found         = 0;
	auto   followup      = contCon.followup;
	auto   followupWrite = contCon.followupWrite;

	if (followup == followupWrite) {

#ifdef __AVX512F__ // if AVX 512 available, use it!
#if HASH_SIZE == 32
		size_t rest = cont.numProbes % 8;
		auto   ids  = _mm512_set_epi32(0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0);
		for (size_t i = 0, end = cont.numProbes - rest; i < end; i += 8) {

			// load hashes
			// auto hash = probeHashes[i];
			auto  hashDense = _mm256_loadu_si256((const __m256i*)(probeHashes + i));
			Vec8u hashes    = _mm512_cvtepu32_epi64(hashDense);
			// Vec8u hashes(probeHashes + i);
			// find entry pointers in ht
			Vec8uM entries = shared.ht.find_chain_tagged(hashes);
			// load entry hashes
			Vec8u hashPtrs    = entries.vec + Vec8u(offsetof(decltype(shared.ht)::EntryHeader, hash));
			auto  entryHashes = _mm512_mask_i64gather_epi32(hashDense, entries.mask, hashPtrs, nullptr, 1);
			{
				// Check if hashes match
				__mmask8 hashesEq = _mm512_mask_cmpeq_epi32_mask(
				    entries.mask, _mm512_castsi256_si512(entryHashes), _mm512_castsi256_si512(hashDense));
				// write pointers
				_mm512_mask_compressstoreu_epi64(buildMatches + found, hashesEq, entries.vec);
				static_assert(sizeof(pos_t) == 4,
				              "SIMD join assumes sizeof(pos_t) is 4"); // change the
				                                                       // types for
				                                                       // probeSels
				                                                       // if this
				                                                       // fails
				// write selection
				__m512i probeSels = _mm512_loadu_si512(probeSel + i);
				_mm512_mask_compressstoreu_epi32(probeMatches + found, hashesEq, probeSels);
				found += __builtin_popcount(hashesEq);
			}

			{
				// write continuations
				static_assert(offsetof(decltype(shared.ht)::EntryHeader, next) == 0,
				              "Hash is expected to be in first position");
				Vec8u    nextPtrs = _mm512_mask_i64gather_epi64(entries.vec, entries.mask, entries.vec, nullptr, 1);
				__mmask8 hasNext =
				    _mm512_mask_cmpneq_epi64_mask(entries.mask, nextPtrs, Vec8u(uint64_t(shared.ht.end())));
				if (hasNext) {
					// write pointers
					_mm512_mask_compressstoreu_epi64(followupEntries + followupWrite, hasNext, nextPtrs);
					static_assert(sizeof(pos_t) == 4,
					              "SIMD join assumes sizeof(pos_t) is 4"); // change the types
					                                                       // for probeSels if
					                                                       // this fails
					// write selection
					_mm512_mask_compressstoreu_epi32(followupIds + followupWrite, hasNext, ids);
					followupWrite += __builtin_popcount(hasNext);
				}
				ids = _mm512_add_epi32(ids, _mm512_set1_epi32(8));
			}
		}
#else
		size_t rest = cont.numProbes % 8;
		auto   ids  = _mm512_set_epi32(0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0);
		for (size_t i = 0, end = cont.numProbes - rest; i < end; i += 8) {

			// load hashes
			// auto hash = probeHashes[i];
			Vec8u hashes(probeHashes + i);
			// find entry pointers in ht
			Vec8uM entries = shared.ht.find_chain_tagged(hashes);
			// load entry hashes
			Vec8u hashPtrs    = entries.vec + Vec8u(offsetof(decltype(shared.ht)::EntryHeader, hash));
			Vec8u entryHashes = _mm512_mask_i64gather_epi64(hashPtrs, entries.mask, hashPtrs, nullptr, 1);
			{
				// Check if hashes match
				__mmask8 hashesEq = _mm512_mask_cmpeq_epi64_mask(entries.mask, entryHashes, hashes);
				// write pointers
				_mm512_mask_compressstoreu_epi64(buildMatches + found, hashesEq, entries.vec);
				static_assert(sizeof(pos_t) == 4,
				              "SIMD join assumes sizeof(pos_t) is 4"); // change the
				                                                       // types for
				                                                       // probeSels
				                                                       // if this
				                                                       // fails
				// write selection
				__m512i probeSels = _mm512_loadu_si512(probeSel + i);
				_mm512_mask_compressstoreu_epi32(probeMatches + found, hashesEq, probeSels);
				found += __builtin_popcount(hashesEq);
			}

			{
				// write continuations
				static_assert(offsetof(decltype(shared.ht)::EntryHeader, next) == 0,
				              "Hash is expected to be in first position");
				Vec8u    nextPtrs = _mm512_mask_i64gather_epi64(entries.vec, entries.mask, entries.vec, nullptr, 1);
				__mmask8 hasNext =
				    _mm512_mask_cmpneq_epi64_mask(entries.mask, nextPtrs, Vec8u(uint64_t(shared.ht.end())));
				if (hasNext) {
					// write pointers
					_mm512_mask_compressstoreu_epi64(followupEntries + followupWrite, hasNext, nextPtrs);
					static_assert(sizeof(pos_t) == 4,
					              "SIMD join assumes sizeof(pos_t) is 4"); // change the types
					                                                       // for probeSels if
					                                                       // this fails
					// write selection
					_mm512_mask_compressstoreu_epi32(followupIds + followupWrite, hasNext, ids);
					followupWrite += __builtin_popcount(hasNext);
				}
				ids = _mm512_add_epi32(ids, _mm512_set1_epi32(8));
			}
		}
#endif // hash size
#else
		const size_t rest = cont.numProbes;
#endif
		for (size_t i = cont.numProbes - rest, end = cont.numProbes; i < end; ++i) {
			auto hash  = probeHashes[i];
			auto entry = shared.ht.find_chain_tagged(hash);
			if (entry != shared.ht.end()) {
				if (entry->hash == hash) {
					buildMatches[found] = entry;
					probeMatches[found] = probeSel[i];
					found += 1;
				}
				if (entry->next != shared.ht.end()) {
					followupIds[followupWrite]     = i;
					followupEntries[followupWrite] = entry->next;
					followupWrite += 1;
				}
			}
		}
	}

	followupWrite %= followupBufferSize;

	while (followup != followupWrite) {
		auto remainingSpace = batchSize - found;
		auto nrFollowups =
		    followup <= followupWrite ? followupWrite - followup : followupBufferSize - (followup - followupWrite);
		auto fittingElements = std::min((size_t)nrFollowups, remainingSpace);
		for (size_t j = 0; j < fittingElements; ++j) {
			size_t i     = followupIds[followup];
			auto   entry = followupEntries[followup];
			followup     = (followup + 1) % followupBufferSize;
			auto hash    = probeHashes[i];
			if (entry->hash == hash) {
				buildMatches[found]   = entry;
				probeMatches[found++] = probeSel[i];
			}
			if (entry->next != shared.ht.end()) {
				followupIds[followupWrite]     = i;
				followupEntries[followupWrite] = entry->next;
				followupWrite                  = (followupWrite + 1) % followupBufferSize;
			}
		}
		if (fittingElements < nrFollowups) {
			// continuation
			contCon.followupWrite = followupWrite;
			contCon.followup      = followup;
			return found;
		}
	}
	cont.nextProbe        = cont.numProbes;
	contCon.followup      = 0;
	contCon.followupWrite = 0;
	return found;
}

template <typename T, typename HT>
void INTERPRET_SEPARATE insertAllEntries(T& allocations, HT& ht, size_t ht_entry_size) {
	for (auto& block : allocations) {
		auto start = reinterpret_cast<runtime::Hashmap::EntryHeader*>(block.first);
		ht.insertAll_tagged(start, block.second, ht_entry_size);
	}
}

pos_t Hashjoin::joinBoncz() {
	size_t followupWrite = contCon.followupWrite;
	size_t found         = 0;
	if (followupWrite == 0)
		for (size_t i = 0, end = cont.numProbes; i < end; ++i) {
			auto hash  = probeHashes[i];
			auto entry = shared.ht.find_chain_tagged(hash);
			if (entry != shared.ht.end()) {
				followupIds[followupWrite]     = i;
				followupEntries[followupWrite] = entry;
				followupWrite += 1;
			}
		}

	while (followupWrite > 0) {
		size_t e      = followupWrite;
		followupWrite = 0;
		for (size_t j = 0; j < e; j++) {
			auto i     = followupIds[j];
			auto entry = followupEntries[j];
			// auto hash = probeHashes[i];
			// if (entry->hash == hash) {
			buildMatches[found]   = entry;
			probeMatches[found++] = i;
			// }
			if (entry->next) {
				followupIds[followupWrite]       = i;
				followupEntries[followupWrite++] = entry->next;
			}
		}
		if (followupWrite == 0) {
			cont.nextProbe        = cont.numProbes;
			contCon.followupWrite = followupWrite;
			return found;
		} else if (found + followupWrite >= batchSize) {
			contCon.followupWrite = followupWrite;
			assert(found);
			return found;
		}
	}
	cont.nextProbe        = cont.numProbes;
	contCon.followupWrite = followupWrite;
	return 0;
}

size_t Hashjoin::next() {
	using runtime::Hashmap;
	// --- build
	if (!consumed) {
		size_t found = 0;
		// --- build phase 1: materialize ht entries
		for (auto n = left->next(); n != EndOfStream; n = left->next()) {
			found += n;
			// build hashes
			buildHash.evaluate(n);
			// scatter hash, keys and values into ht entries
			auto alloc = runtime::this_worker->allocator.allocate(n * ht_entry_size);
			if (!alloc) throw std::runtime_error("malloc failed");
			allocations.push_back(std::make_pair(alloc, n));
			scatterStart = reinterpret_cast<decltype(scatterStart)>(alloc);
			buildScatter.evaluate(n);
		}

		// --- build phase 2: insert ht entries
		shared.found.fetch_add(found);
		barrier([&]() {
			auto globalFound = shared.found.load();
			if (globalFound) shared.ht.setSize(globalFound);
		});
		auto globalFound = shared.found.load();
		if (globalFound == 0) {
			consumed = true;
			return EndOfStream;
		}
		insertAllEntries(allocations, shared.ht, ht_entry_size);
		consumed = true;
		barrier(); // wait for all threads to finish build phase
	}
	// --- lookup
	while (true) {
		if (cont.nextProbe >= cont.numProbes) {
			cont.numProbes = right->next();
			cont.nextProbe = 0;
			if (cont.numProbes == EndOfStream) return EndOfStream;
			probeHash.evaluate(cont.numProbes);
		}
		// create join pair vectors with matching hashes (Entry*, pos), where
		// Entry* is for the build side, pos a selection index to the right side
		auto n = (this->*join)();
		// check key equality and remove non equal keys from join result
		n = keyEquality.evaluate(n);
		if (n == 0) continue;
		// materialize build side
		buildGather.evaluate(n);
		return n;
	}
}

Hashjoin::Hashjoin(Shared& sm)
    : shared(sm) {}

Hashjoin::~Hashjoin() {
	// for (auto& block : allocations) free(block.first);
}

HashGroup::HashGroup(Shared& s)
    : shared(s)
    , preAggregation(*this)
    , globalAggregation(*this) {
	maxFill = ht.setSize(initialMapSize);
}
HashGroup::~HashGroup() {
	// for (auto& alloc : preAggregation.allocations) free(alloc.first);
	// for (auto& alloc : globalAggregation.allocations) free(alloc.first);
}

pos_t HashGroup::findGroupsFromPartition(void* data, size_t n) {
	globalAggregation.groupHashes = reinterpret_cast<hash_t*>(data);
	return globalAggregation.findGroups(n, ht);
}

size_t HashGroup::next() {
	using header_t = decltype(ht)::EntryHeader;
	if (!cont.consumed) {
		/// ------ phase 1: local preaggregation
		/// aggregate all incoming tuples into local hashtable
		size_t groups     = 0;
		auto&  spill      = shared.spillStorage.local();
		auto   entry_size = preAggregation.ht_entry_size;

		auto flushAndClear = [&]() INTERPRET_SEPARATE {
			assert(offsetof(header_t, next) + sizeof(header_t::next) == offsetof(header_t, hash));
			// flush ht entries into spillStorage
			for (auto& alloc : preAggregation.allocations) {
				for (auto entry = reinterpret_cast<header_t*>(alloc.first),
				          end   = addBytes(entry, alloc.second * entry_size);
				     entry < end;
				     entry = addBytes(entry, entry_size))
					spill.push_back(&entry->hash, entry->hash);
			}
			preAggregation.allocations.clear();
			preAggregation.clearHashtable(ht);
		};

		for (pos_t n = child->next(); n != EndOfStream; n = child->next()) {
			groupHash.evaluate(n);
			preAggregation.findGroups(n, ht);
			auto groupsCreated = preAggregation.createMissingGroups(ht, false);
			updateGroups.evaluate(n);
			groups += groupsCreated;
			if (groups >= maxFill) flushAndClear();
		}
		flushAndClear(); // flush remaining entries into spillStorage
		barrier();       // Wait until all workers have finished phase 1

		cont.consumed                  = true;
		cont.partition                 = shared.partition.fetch_add(1);
		cont.partitionNeedsAggregation = true;
	}

	/// ------ phase 2: global aggregation
	// get a partition
	for (; cont.partition < nrPartitions;) {
		if (cont.partitionNeedsAggregation) {
			auto partNr = cont.partition;
			// for all thread local partitions
			for (auto& threadPartitions : shared.spillStorage.threadData) {
				// aggregate data from thread local partition
				auto& partition = threadPartitions.second.getPartitions()[partNr];
				for (auto chunk = partition.first; chunk; chunk = chunk->next) {
					auto elementSize = threadPartitions.second.entrySize;
					auto nPart       = partition.size(chunk, elementSize);
					for (size_t n = std::min(nPart, vecSize), pos = 0; n;
					     nPart -= n, pos += n, n = std::min(nPart, vecSize)) {

						// communicate data position of current chunk to primitives
						// for group lookup and creation
						auto data                 = addBytes(chunk->data<void>(), pos * elementSize);
						globalAggregation.rowData = data;
						findGroupsFromPartition(data, n);
						auto cGroups = [&]() INTERPRET_SEPARATE {
							globalAggregation.createMissingGroups(ht, true);
						};
						cGroups();
						updateGroupsFromPartition.evaluate(n);
					}
				}
			}
			cont.partitionNeedsAggregation = false;
			cont.iter                      = globalAggregation.allocations.begin();
		}
		// send aggregation result to parent operator
		// TODO: refill result instead of sending all allocations separately
		if (cont.iter != globalAggregation.allocations.end()) {
			auto& block = *cont.iter;
			// write current block start to htMatches so the the gather primitives
			// can read the offset from there
			*globalAggregation.htMatches = reinterpret_cast<header_t*>(block.first);
			auto n                       = block.second;
			gatherGroups.evaluate(n);
			cont.iter++;
			return n;
		} else {
			auto htClear = [&]() INTERPRET_SEPARATE {
				globalAggregation.clearHashtable(ht);
			};
			htClear();
			cont.partitionNeedsAggregation = true;
			cont.partition                 = shared.partition.fetch_add(1);
		}
	}
	return EndOfStream;
}
} // namespace vectorwise
