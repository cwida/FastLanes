#include "data.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/printer/az_printer.hpp"
#include "gtest/gtest.h"
#include <chrono>     // for std::chrono::steady_clock, duration, etc.
#include <filesystem> // for std::filesystem
#include <fls/cor/prm/fsst12/fsst12.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// NOLINTBEGIN

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wimplicit-int-float-conversion"

using namespace std;
namespace fs = std::filesystem;

/// FSST compression
class FSSTCompressionRunner {
private:
	/// The decode
	fsst_decoder_t decoder;
	/// The compressed data
	vector<unsigned char> compressedData;
	/// The offsets
	vector<unsigned> offsets;

public:
	static string get_name() {
		return "FSST";
	}
	FSSTCompressionRunner() = default;
	FSSTCompressionRunner(unsigned /*blockSizeIgnored*/) {
	}

	/// Store the compressed corpus. Returns the compressed size
	uint64_t compressCorpus(
	    const vector<string>& data, unsigned long& bareSize, double& bulkTime, double& compressionTime, bool verbose) {
		compressedData.clear();
		offsets.clear();

		vector<uint32_t>       rowLens, compressedRowLens;
		vector<unsigned char*> rowPtrs, compressedRowPtrs;
		rowLens.reserve(data.size());
		compressedRowLens.resize(data.size());
		rowPtrs.reserve(data.size());
		compressedRowPtrs.resize(data.size() + 1);
		uint32_t totalLen = 0;
		for (auto& d : data) {
			totalLen += d.size();
			rowLens.push_back(d.size());
			rowPtrs.push_back(reinterpret_cast<unsigned char*>(const_cast<char*>(d.data())));
		}

		auto                  firstTime  = std::chrono::steady_clock::now();
		auto                  encoder    = fsst_create(data.size(), rowLens.data(), rowPtrs.data(), false);
		auto                  createTime = std::chrono::steady_clock::now();
		vector<unsigned char> compressionBuffer, fullBuffer;
		fullBuffer.resize(totalLen);
		unsigned char* fullBuf   = fullBuffer.data();
		unsigned       stringEnd = 0;
		for (auto& d : data) {
			memcpy(fullBuf + stringEnd, d.data(), d.length());
			stringEnd += d.length();
		}
		compressionBuffer.resize(16 + 2 * totalLen);
		auto copyTime = std::chrono::steady_clock::now();
		fsst_compress(encoder,
		              1,
		              &totalLen,
		              &fullBuf,
		              compressionBuffer.size(),
		              compressionBuffer.data(),
		              compressedRowLens.data(),
		              compressedRowPtrs.data());
		auto startTime = std::chrono::steady_clock::now();
		fsst_compress(encoder,
		              data.size(),
		              rowLens.data(),
		              rowPtrs.data(),
		              compressionBuffer.size(),
		              compressionBuffer.data(),
		              compressedRowLens.data(),
		              compressedRowPtrs.data());
		auto          stopTime = std::chrono::steady_clock::now();
		unsigned long compressedLen =
		    data.empty()
		        ? 0
		        : (compressedRowPtrs[data.size() - 1] + compressedRowLens[data.size() - 1] - compressionBuffer.data());

		az_printer::yellow_cout << "-- compressedLen: " << compressedLen << std::endl;

		compressedData.resize(compressedLen + 8192);
		memcpy(compressedData.data(), compressionBuffer.data(), compressedLen);
		offsets.reserve(data.size());
		compressedRowPtrs[data.size()] = compressionBuffer.data() + compressedLen;
		for (unsigned index = 0, limit = data.size(); index != limit; ++index)
			offsets.push_back(compressedRowPtrs[index + 1] - compressionBuffer.data());
		bareSize        = compressedData.size();
		uint64_t result = bareSize + (offsets.size() * sizeof(unsigned));
		{
			unsigned char buffer[sizeof(fsst_decoder_t)];
			unsigned      dictLen = fsst_export(encoder, buffer);
			az_printer::yellow_cout << "-- dictLen: " << dictLen << std::endl;

			fsst_destroy(encoder);
			result += dictLen;

			auto symbol_table_size = fsst_import(&decoder, buffer);
			az_printer::yellow_cout << "-- symbol_table_size: " << symbol_table_size << std::endl;
		}
		double oneTime  = std::chrono::duration<double>(createTime - firstTime).count();
		bulkTime        = std::chrono::duration<double>(startTime - copyTime).count();
		compressionTime = std::chrono::duration<double>(stopTime - startTime).count();
		if (verbose) {
			cout << "# symbol table construction time: " << oneTime << endl;
			cout << "# compress-bulk time: " << bulkTime << endl;
			cout << "# compress time: " << compressionTime << endl;
		}
		bulkTime += oneTime;
		compressionTime += oneTime;

		return result;
	}

	/// Decompress some selected rows, separated by newlines. The line number are in ascending order. The target buffer
	/// is guaranteed to be large enough
	uint64_t decompressRows(vector<char>& target, const vector<unsigned>& lines) {
		char* writer = target.data();
		auto  limit  = writer + target.size();

		auto data    = compressedData.data();
		auto offsets = this->offsets.data();
		for (auto l : lines) {
			auto     start = l ? offsets[l - 1] : 0, end = offsets[l];
			unsigned len = fsst_decompress(
			    &decoder, end - start, data + start, limit - writer, reinterpret_cast<unsigned char*>(writer));
			writer[len] = '\n';
			writer += len + 1;
		}
		return writer - target.data();
	}

	void validate(vector<char>& target, const vector<unsigned>& lines, const vector<string>& origin) {
		char* writer = target.data();
		auto  limit  = writer + target.size();

		auto data    = compressedData.data();
		auto offsets = this->offsets.data();

		for (auto l : lines) {
			auto     start = l ? offsets[l - 1] : 0, end = offsets[l];
			unsigned len = fsst_decompress(
			    &decoder, end - start, data + start, limit - writer, reinterpret_cast<unsigned char*>(writer));

			if (origin[l].size() != len || origin[l].compare(0, len, target.data(), len) != 0) {
				cerr << "corpus[" << l << "] decompression failed!" << endl;
				return;
			}
		}
	}
};

/// FSST compression
class FSST12CompressionRunner {
private:
	/// The decode
	fsst12_decoder_t decoder;
	/// The compressed data
	vector<unsigned char> compressedData;
	/// The offsets
	vector<unsigned> offsets;

public:
	static string get_name() {
		return "FSST12";
	}
	FSST12CompressionRunner() = default;

	/// Store the compressed corpus. Returns the compressed size
	uint64_t compressCorpus(
	    const vector<string>& data, unsigned long& bareSize, double& bulkTime, double& compressionTime, bool verbose) {
		compressedData.clear();
		offsets.clear();

		vector<uint32_t>       rowLens, compressedRowLens;
		vector<unsigned char*> rowPtrs, compressedRowPtrs;
		rowLens.reserve(data.size());
		compressedRowLens.resize(data.size());
		rowPtrs.reserve(data.size());
		compressedRowPtrs.resize(data.size() + 1);
		uint32_t totalLen = 0;
		for (auto& d : data) {
			totalLen += d.size();
			rowLens.push_back(d.size());
			rowPtrs.push_back(reinterpret_cast<unsigned char*>(const_cast<char*>(d.data())));
		}

		auto                  firstTime  = std::chrono::steady_clock::now();
		auto                  encoder    = fsst12_create(data.size(), rowLens.data(), rowPtrs.data(), false);
		auto                  createTime = std::chrono::steady_clock::now();
		vector<unsigned char> compressionBuffer, fullBuffer;
		fullBuffer.resize(totalLen);
		unsigned char* fullBuf   = fullBuffer.data();
		unsigned       stringEnd = 0;
		for (auto& d : data) {
			memcpy(fullBuf + stringEnd, d.data(), d.length());
			stringEnd += d.length();
		}
		compressionBuffer.resize(16 + 2 * totalLen);
		auto copyTime = std::chrono::steady_clock::now();
		fsst12_compress(encoder,
		                1,
		                &totalLen,
		                &fullBuf,
		                compressionBuffer.size(),
		                compressionBuffer.data(),
		                compressedRowLens.data(),
		                compressedRowPtrs.data());
		auto startTime = std::chrono::steady_clock::now();
		fsst12_compress(encoder,
		                data.size(),
		                rowLens.data(),
		                rowPtrs.data(),
		                compressionBuffer.size(),
		                compressionBuffer.data(),
		                compressedRowLens.data(),
		                compressedRowPtrs.data());
		auto          stopTime = std::chrono::steady_clock::now();
		unsigned long compressedLen =
		    data.empty()
		        ? 0
		        : (compressedRowPtrs[data.size() - 1] + compressedRowLens[data.size() - 1] - compressionBuffer.data());

		compressedData.resize(compressedLen + 8192);
		memcpy(compressedData.data(), compressionBuffer.data(), compressedLen);
		offsets.reserve(data.size());
		compressedRowPtrs[data.size()] = compressionBuffer.data() + compressedLen;
		for (unsigned index = 0, limit = data.size(); index != limit; ++index)
			offsets.push_back(compressedRowPtrs[index + 1] - compressionBuffer.data());
		bareSize        = compressedData.size();
		uint64_t result = bareSize + (offsets.size() * sizeof(unsigned));
		{
			unsigned char buffer[sizeof(fsst12_decoder_t)];
			unsigned      dictLen = fsst12_export(encoder, buffer);
			fsst12_destroy(encoder);
			result += dictLen;

			fsst12_import(&decoder, buffer);
		}
		double oneTime  = std::chrono::duration<double>(createTime - firstTime).count();
		bulkTime        = std::chrono::duration<double>(startTime - copyTime).count();
		compressionTime = std::chrono::duration<double>(stopTime - startTime).count();
		if (verbose) {
			cout << "# symbol table construction time: " << oneTime << endl;
			cout << "# compress-bulk time: " << bulkTime << endl;
			cout << "# compress time: " << compressionTime << endl;
		}
		bulkTime += oneTime;
		compressionTime += oneTime;

		return result;
	}

	/// Decompress some selected rows, separated by newlines. The line number are in ascending order. The target buffer
	/// is guaranteed to be large enough
	uint64_t decompressRows(vector<char>& target, const vector<unsigned>& lines) {
		char* writer = target.data();
		auto  limit  = writer + target.size();

		auto data    = compressedData.data();
		auto offsets = this->offsets.data();
		for (auto l : lines) {
			auto     start = l ? offsets[l - 1] : 0, end = offsets[l];
			unsigned len = fsst12_decompress(
			    &decoder, end - start, data + start, limit - writer, reinterpret_cast<unsigned char*>(writer));
			writer[len] = '\n';
			writer += len + 1;
		}
		return writer - target.data();
	}

	void validate(vector<char>& target, const vector<unsigned>& lines, const vector<string>& origin) {
		char* writer = target.data();
		auto  limit  = writer + target.size();

		auto data    = compressedData.data();
		auto offsets = this->offsets.data();

		for (auto l : lines) {
			auto     start = l ? offsets[l - 1] : 0, end = offsets[l];
			unsigned len = fsst12_decompress(
			    &decoder, end - start, data + start, limit - writer, reinterpret_cast<unsigned char*>(writer));

			if (origin[l].size() != len || origin[l].compare(0, len, target.data(), len) != 0) {
				cerr << "corpus[" << l << "] decompression failed!" << endl;
				return;
			}
		}
	}
};

template <class T>
void benchmark_file(const string& file, string_view file_name, ofstream& result_file, bool extend) {

	unsigned long      bareSize = 0, totalSize = 0;
	double             bulkTime = 0, compressionTime = 0, decompressionTime = 0, compressionRatio;
	T                  runner;
	constexpr unsigned repeat = 100;

	// Read the corpus
	vector<string>     corpus;
	uint64_t           corpusLen = 0;
	constexpr uint64_t targetLen = 8 << 20;

	ifstream in(file);
	if (!in.is_open()) {
		cerr << "unable to open " << file << endl;
		exit(1);
	}
	string line;
	while (getline(in, line)) {
		corpusLen += line.length() + 1;
		corpus.push_back(std::move(line));
		if (corpusLen > targetLen)
			break;
	}
	if (corpus.empty())
		return;
	if (extend) {
		unsigned reader = 0;
		while (corpusLen < targetLen) {
			corpusLen += corpus[reader].length() + 1;
			corpus.push_back(corpus[reader++]);
		}
	}

	// Compress it
	totalSize += runner.compressCorpus(corpus, bareSize, bulkTime, compressionTime, false);
	compressionRatio = static_cast<double>(corpusLen) / totalSize;

	// Prepare hits vector counts
	vector<unsigned> hits;
	for (unsigned index = 0, limit = corpus.size(); index != limit; ++index)
		hits.push_back(index);

	vector<char> targetBuffer;
	targetBuffer.resize(corpusLen + 4096);
	{
		for (unsigned index = 0; index != repeat; ++index) {
			runner.decompressRows(targetBuffer, hits);
		}
		auto startTime = std::chrono::steady_clock::now();
		for (unsigned index = 0; index != repeat; ++index) {
			runner.decompressRows(targetBuffer, hits);
		}
		auto stopTime = std::chrono::steady_clock::now();
		decompressionTime += std::chrono::duration<double>(stopTime - startTime).count();
	}

	// validation:

	runner.validate(targetBuffer, hits, corpus);

	result_file << file_name <<                                                //
	    "," << static_cast<double>(corpusLen) / bareSize                       //
	            << "," << (corpusLen / bulkTime) / (1 << 20)                   //
	            << "," << compressionRatio                                     //
	            << "," << (corpusLen / compressionTime) / (1 << 20)            //
	            << "," << (corpusLen * repeat / decompressionTime) / (1 << 20) //
	            << std::endl;
}

template <class T>
vector<pair<unsigned, double>> cmpFilter(unsigned blockSize, const vector<string>& files) {
	T    runner(blockSize);
	auto res = doTest(runner, files, false);
	if (!res.first)
		exit(1);
	return res.second;
}

template <typename BENCHMAKER, int N>
void run_benchmarks(std::array<std::pair<string_view, string_view>, N> name_to_path_map,
                    std::string_view                                   result_file_path,
                    bool                                               extend) {

	const fs::path result_path(result_file_path);
	std::ofstream  out(result_path);

	if (!out.is_open()) {
		std::cerr << "Unable to open " << result_path << std::endl;
		return;
	}

	out << "file_name,"
	    << "compression_ratio,"
	    << "throughput_bulk (MB/s),"
	    << "compression_ratio,"
	    << "throughput_compression (MB/s),"
	    << "throughput_decompression (MB/s)," //
	    << std::endl;                         //

	for (const auto& [file_name, file] : name_to_path_map) {
		az_printer::green_cout << "-- Benchmarking " << file_name << " " << BENCHMAKER::get_name() << std::endl;
		benchmark_file<BENCHMAKER>(std::string {file}, file_name, out, extend);
		az_printer::green_cout << "-- " << file_name << " is benchmarked successfully with " << BENCHMAKER::get_name()
		                       << std::endl;
	}
}

class TestFsst : public ::testing::Test {};

TEST_F(TestFsst, fsst_test_data) {
	constexpr std::string_view result_file_path = FSST_CMAKE_SOURCE_DIR "/benchmarks/results/fsst/test.csv";
	run_benchmarks<FSSTCompressionRunner, 1>(data::test::NAME_TO_PATH_MAP, result_file_path, false);
}

TEST_F(TestFsst, fsst_dbtext) {
	constexpr std::string_view result_file_path = FSST_CMAKE_SOURCE_DIR "/benchmarks/results/fsst/dbtext.csv";
	run_benchmarks<FSSTCompressionRunner, 23>(data::dbtext::NAME_TO_PATH_MAP, result_file_path, true);
}

TEST_F(TestFsst, fsst12_test_data) {
	constexpr std::string_view result_file_path = FSST_CMAKE_SOURCE_DIR "/benchmarks/results/fsst12/test.csv";
	run_benchmarks<FSST12CompressionRunner, 1>(data::test::NAME_TO_PATH_MAP, result_file_path, false);
}

TEST_F(TestFsst, fsst12_dbtext) {
	constexpr std::string_view result_file_path = FSST_CMAKE_SOURCE_DIR "/benchmarks/results/fsst12/dbtext.csv";
	run_benchmarks<FSST12CompressionRunner, 23>(data::dbtext::NAME_TO_PATH_MAP, result_file_path, true);
}

#pragma clang diagnostic pop

// NOLINTEND
