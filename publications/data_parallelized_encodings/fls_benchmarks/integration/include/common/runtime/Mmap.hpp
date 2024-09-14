#pragma once
#include "benchmarks/fls/config.hpp"
#include "common/Compat.hpp"
#include "fls/pack.hpp"
#include <cassert>
#include <cstring>
#include <experimental/string_view>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

// clang-format off
DIAGNOSTIC_PUSH_NO_UNKNOWN
DIAGNOSTIC_PUSH(-Wterminate)
// clang-format on
#define check(expr)                                                                                                    \
	if (!(expr)) {                                                                                                     \
		perror(#expr);                                                                                                 \
		throw;                                                                                                         \
	}
DIAGNOSTIC_POP
DIAGNOSTIC_POP

namespace runtime {

template <class K, class V>
struct HashTable {
	struct HT {
		uint64_t hashTableMask;
		uint64_t array[];
	};

	struct HashTableVector {
		uint64_t count;
		uint64_t next;
		K        key;
		V        values[];

		const V* begin() const { return values; }
		const V* end() const { return values + count; }
		const V& operator[](size_t idx) const { return values[idx]; }
		uint64_t size() const { return count; }
	};

	uint64_t fileSize;
	int      fd;
	HT*      hashTable;

	void readBinary(const char* pathname) {
		fd = open(pathname, O_RDONLY);
		check(fd != -1);
		struct stat sb;
		check(fstat(fd, &sb) != -1);
		fileSize  = static_cast<uint64_t>(sb.st_size);
		hashTable = reinterpret_cast<HT*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
		check(hashTable != MAP_FAILED);
	}

	static void writeBinary(const char* pathname, std::unordered_map<K, std::vector<V>>& m) {
		int fd = open(pathname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		check(fd != -1);
		uint64_t bits = 1;
		while ((1ull << bits) < (m.size() * 1.5))
			bits++;
		uint64_t space = sizeof(HT) + ((1ull << bits) * sizeof(uint64_t));
		for (auto p : m)
			space += sizeof(HashTableVector) + (sizeof(V) * p.second.size());
		check(compat::posix_fallocate(fd, 0, space) == 0);
		HT* data = reinterpret_cast<HT*>(mmap(nullptr, space, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		check(data != MAP_FAILED);
		uint64_t mask       = (1ull << bits) - 1;
		data->hashTableMask = mask;
		memset(data->array, 0, (1ull << bits) * sizeof(uint64_t));
		uint8_t* ptr    = reinterpret_cast<uint8_t*>(data);
		uint64_t offset = sizeof(HT) + ((1ull << bits) * sizeof(uint64_t));
		for (auto p : m) {
			HashTableVector* e = reinterpret_cast<HashTableVector*>(ptr + offset);
			e->key             = p.first;
			e->count           = p.second.size();
			uint64_t pos       = hash(p.first) & mask;
			e->next            = data->array[pos];
			data->array[pos]   = offset;
			memcpy(e->values, p.second.data(), (p.second.size() * sizeof(V)));
			offset += sizeof(HashTableVector) + (p.second.size() * sizeof(V));
		}
		assert(offset == space);
		check(close(fd) == 0);
	}

	static uint64_t hash(K key) {
		uint64_t       k = static_cast<uint64_t>(key);
		const uint64_t m = 0xc6a4a7935bd1e995;
		const int      r = 47;
		uint64_t       h = 0x8445d61a4e774912 ^ (8 * m);
		k *= m;
		k ^= k >> r;
		k *= m;
		h ^= k;
		h *= m;
		h ^= h >> r;
		h *= m;
		h ^= h >> r;
		return h | (1ull << 63);
	}

	HashTable()
	    : hashTable(nullptr) {
		empty.count = 0;
	}
	HashTable(const char* pathname)
	    : HashTable() {
		readBinary(pathname);
	}
	~HashTable() noexcept(false) {
		if (hashTable) check(munmap(hashTable, fileSize) == 0);
	}

	HashTableVector empty;

	const HashTableVector& operator[](K key) {
		uint64_t pos = hashTable->array[hash(key) & hashTable->hashTableMask];
		while (pos) {
			HashTableVector* e = reinterpret_cast<HashTableVector*>(reinterpret_cast<uint8_t*>(hashTable) + pos);
			if (e->key == key) return *e;
			pos = e->next;
		}
		return empty;
	}
};

template <class T>
class Vector {
public:
	Vector()
	    : count(0)
	    , data_(nullptr)
	    , persistent(false) {}
	Vector(const char* pathname)
	    : count(0)
	    , data_(nullptr)
	    , persistent(true) {
		readBinary(pathname);
	}
	Vector(Vector&&)      = default;
	Vector(const Vector&) = delete;
	~Vector() noexcept(false) {
		if (data_) {
			if (persistent) {
				check(munmap(data_, count * dataSize) == 0);
			} else {
				free(data_);
			}
			data_ = nullptr;
		}
	} //
public:
	static void writeBinary(const char* pathname, std::vector<T>& v);
	static void write_bitpacked_binary(const char* pathname, std::vector<T>& v);

	void readBinary(const char* pathname) {
		fd = open(pathname, O_RDONLY);
		check(fd != -1);
		struct stat sb;
		check(fstat(fd, &sb) != -1);
		count = static_cast<uint64_t>(sb.st_size) / sizeof(T);
		if (data_) {
			if (persistent) {
				check(munmap(data_, count * sizeof(T)) == 0);
			} else {
				free(data_);
			}
			data_ = nullptr;
		}
		data_    = reinterpret_cast<T*>(mmap(nullptr, count * sizeof(T), PROT_READ, MAP_PRIVATE, fd, 0));
		dataSize = sizeof(T);
		check(data_ != MAP_FAILED);
		persistent = true;
	}
	uint64_t size() const { return count; }
	T*       data() const { return data_; }
	T*       begin() const { return data_; }
	T*       end() const { return data_ + count; }
	void     reset(size_t n) {
		    if (persistent) throw std::runtime_error("Can't resize persistent Vector");
        if (data_) free(data_);
        data_ = reinterpret_cast<T*>(compat::aligned_alloc(16, sizeof(T) * n));
		    count = 0;
	}
	void push_back(T& el) {
		assert(!persistent);
		data_[count++] = el;
	}
	T&       operator[](std::size_t idx) { return data_[idx]; }
	const T& operator[](std::size_t idx) const { return data_[idx]; } //
private:
	uint64_t count;
	T*       data_ = nullptr;
	size_t   dataSize;
	int      fd;
	bool     persistent;
};

template <class T>
void Vector<T>::write_bitpacked_binary(const char* pathname, std::vector<T>& v) {
	int fd = open(pathname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	check(fd != -1);
	uint64_t bitpacked_length = v.size() * cfg::bw / (sizeof(T) * 8 / 4);
	check(compat::posix_fallocate(fd, 0, bitpacked_length) == 0);
	T* data = reinterpret_cast<T*>(mmap(nullptr, bitpacked_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	check(data != MAP_FAILED);

	size_t bitpack_j = cfg::vec_c * cfg::bw / (sizeof(T) * 8);
	size_t ttl_vec_c = v.size() / cfg::vec_c;
	for (size_t i {0}; i < ttl_vec_c; ++i) {
		generated::pack::fallback::scalar::pack(reinterpret_cast<uint32_t*>(v.data() + i * cfg::vec_c),
		                                        reinterpret_cast<uint32_t*>(data + i * bitpack_j),
		                                        cfg::bw);
	}

	check(close(fd) == 0);
}

template <class T>
void Vector<T>::writeBinary(const char* pathname, std::vector<T>& v) {
	int fd = open(pathname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	check(fd != -1);
	uint64_t length = v.size() * sizeof(T);
	check(compat::posix_fallocate(fd, 0, length) == 0);
	T* data = reinterpret_cast<T*>(mmap(nullptr, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	check(data != MAP_FAILED);
	memcpy(data, v.data(), length);
	check(close(fd) == 0);
}

typedef std::experimental::string_view str;

template <>
struct Vector<str> {
	struct Data {
		uint64_t count;
		struct {
			uint64_t size;
			uint64_t offset;
		} slot[];
	};

	uint64_t fileSize;
	Data*    data_;
	int      fd;
	bool     persistent;

	Vector()
	    : data_(nullptr)
	    , persistent(false) {}
	Vector(const char* pathname)
	    : persistent(true) {
		readBinary(pathname);
	}
	~Vector() noexcept(false) {
		if (data_ && persistent) check(munmap(data_, fileSize) == 0);
	}
	static void writeBinary(const char* pathname, std::vector<std::string>& v) {
		int fd = open(pathname, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		check(fd != -1);
		uint64_t fileSize = 8 + 16 * v.size();
		for (auto s : v)
			fileSize += s.size() + 1;
		check(compat::posix_fallocate(fd, 0, fileSize) == 0);
		auto data =
		    reinterpret_cast<Vector<str>::Data*>(mmap(nullptr, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
		data->count = v.size();
		check(data != MAP_FAILED);
		uint64_t offset = 8 + 16 * v.size();
		char*    dst    = reinterpret_cast<char*>(data);
		uint64_t slot   = 0;
		for (auto s : v) {
			data->slot[slot].size   = s.size();
			data->slot[slot].offset = offset;
			memcpy(dst + offset, s.data(), s.size() + 1);
			offset += s.size() + 1;
			slot++;
		}
		check(close(fd) == 0);
	}

	void readBinary(const char* pathname) {
		fd = open(pathname, O_RDONLY);
		check(fd != -1);
		struct stat sb;
		check(fstat(fd, &sb) != -1);
		fileSize = static_cast<uint64_t>(sb.st_size);
		data_    = reinterpret_cast<Data*>(mmap(nullptr, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
		check(data_ != MAP_FAILED);
	}

	uint64_t size() { return data_->count; }
	Data*    data() const { return data_; }
	str      operator[](std::size_t idx) {
		     auto slot = data_->slot[idx];
		     return str(reinterpret_cast<char*>(data_) + slot.offset, slot.size);
	}
};
} // namespace runtime

#pragma GCC diagnostic pop
