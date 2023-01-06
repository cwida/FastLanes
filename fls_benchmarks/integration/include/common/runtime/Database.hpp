#pragma once
#include "common/algebra/Types.hpp"
#include "common/runtime/MemoryPool.hpp"
#include "common/runtime/Mmap.hpp"
#include "common/runtime/Util.hpp"
#include <deque>
#include <exception>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

using algebra::Type;

namespace runtime {

class Attribute {
public:
	// Attribute() = default;
	Attribute(Attribute&&)      = default;             //
	Attribute(const Attribute&) = delete;              //
	Attribute(std::string n, std::unique_ptr<Type> t); //
public:
	template <typename T>
	T* data() {
		return typedAccess<T>().data();
	}
	void* data() { return data_.data(); }

	template <typename T>
	const runtime::Vector<T>& typedAccess() {
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
		return const_cast<const runtime::Vector<T>&>(reinterpret_cast<runtime::Vector<T>&>(data_));
#pragma GCC diagnostic pop
	}

	template <typename T>
	runtime::Vector<T>& typedAccessForChange() {
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
		return reinterpret_cast<runtime::Vector<T>&>(data_);
#pragma GCC diagnostic pop
	}

	template <typename T>
	void operator=(std::vector<T>&& d) {
		data_.reset(d.size());
		for (auto& el : d)
			typedAccessForChange<T>().push_back(el);
	}

public:
	runtime::Vector<void*> data_;
	std::string            name;
	std::unique_ptr<Type>  type;
};

/* Relation: */
struct Relation {
public:
	Relation()                = default; //
	Relation(Relation&&)      = default; //
	Relation(const Relation&) = delete;  //
public:
	Attribute& operator[](std::string key);                       //
	Attribute& insert(std::string name, std::unique_ptr<Type> t); //
public:
	std::unordered_map<std::string, Attribute> attributes; //
	std::string                                name;       //
	size_t                                     tup_c;      //
};

class BlockRelation {
private:
	struct BlockHeader;

public:
	BlockRelation()                     = default;
	BlockRelation(BlockRelation&&)      = default;
	BlockRelation(const BlockRelation&) = delete;
	~BlockRelation();

	using Attribute = size_t;

	class BlockIter;

	class Block {
		friend BlockIter;

	public:
		/// get pointer to start of data area for Attribute `attr`
		inline void*  data(const Attribute& attr);
		inline void   addedElements(size_t n);
		inline size_t size() const;
		inline size_t spaceRemaining() const;
		Block(BlockRelation* r, BlockHeader* h)
		    : relation(r)
		    , header(h) {}

	protected:
		BlockRelation* relation;
		BlockHeader*   header;
	};

	class BlockIter {
		Block                               b;
		std::vector<BlockHeader*>::iterator vecIter;
		std::vector<BlockHeader*>::iterator vecIterEnd;

	public:
		inline BlockIter(BlockRelation* r, BlockHeader* h, decltype(vecIter) v, decltype(vecIter) vEnd)
		    : b(r, h)
		    , vecIter(v)
		    , vecIterEnd(vEnd) {}
		BlockIter* operator++() noexcept {
			++vecIter;
			if (vecIter != vecIterEnd) b.header = *vecIter;
			return this;
		}

		bool operator!=(const BlockIter& other) const { return vecIter != other.vecIter; }

		Block& operator*() { return b; }
	};

	inline BlockIter begin() {
		if (blocks.size())
			return {this, blocks[0], blocks.begin(), blocks.end()};
		else
			return {this, nullptr, blocks.begin(), blocks.end()};
	}

	inline BlockIter end() { return {this, nullptr, blocks.end(), blocks.end()}; }

	/// Creates a new block for data storage in this relation
	/// Thread save against other calls to this function.
	const size_t     minBlockSize = 128;
	Block            createBlock(size_t minNrElements);
	Attribute        addAttribute(std::string name, size_t elementSize);
	inline Attribute getAttribute(std::string name);

private:
	std::mutex insertMutex;
	struct BlockHeader {
		size_t size;
		size_t maxNrElements;
		BlockHeader(size_t max)
		    : size(0)
		    , maxNrElements(max) {}
		// user data
	};
	size_t currentAttributeSize = 0;
	struct AttributeInfo {
		size_t elementSize;
		size_t offsetInBlock;
		AttributeInfo(size_t e, size_t o)
		    : elementSize(e)
		    , offsetInBlock(o) {}
	};
	std::unordered_map<std::string, Attribute> attributeNames;
	std::deque<AttributeInfo>                  attributes;
	std::vector<BlockHeader*>                  blocks;
};

inline void* BlockRelation::Block::data(const Attribute& attr) {
	return addBytes(header, sizeof(BlockHeader) + relation->attributes[attr].offsetInBlock * header->maxNrElements);
}
inline void BlockRelation::Block::addedElements(size_t n) {
	header->size += n;
	assert(header->size <= header->maxNrElements);
}

inline size_t BlockRelation::Block::size() const { return header->size; }
inline size_t BlockRelation::Block::spaceRemaining() const {
	if (header)
		return header->maxNrElements - header->size;
	else
		return 0;
}

inline BlockRelation::Attribute BlockRelation::getAttribute(std::string name) {
	const auto attrIter = attributeNames.find(name);
	if (attrIter == attributeNames.end()) throw std::runtime_error("Unknown attribute: " + name);
	return attrIter->second;
}

class Database {
	std::unordered_map<std::string, Relation> relations;

public:
	Database()                = default;
	Database(Database&&)      = default;
	Database(const Database&) = delete;
	Relation& operator[](std::string key);
	bool      hasRelation(std::string name);
};
} // namespace runtime
