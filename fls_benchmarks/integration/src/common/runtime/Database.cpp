#include "common/runtime/Database.hpp"
#include "common/runtime/Concurrency.hpp"
#include <cstdlib>

namespace runtime {

Attribute::Attribute(std::string n, std::unique_ptr<Type> t)
    : name(n)
    , type(move(t)) {}

Attribute& Relation::operator[](std::string key) {
	auto att = attributes.find(key);
	if (att != attributes.end())
		return att->second;
	else
		throw std::range_error("Unknown attribute " + key + " in relation " + name);
}

Attribute& Relation::insert(std::string name, std::unique_ptr<Type> t) {
	return attributes
	    .emplace(std::piecewise_construct, std::forward_as_tuple(name), std::forward_as_tuple(name, std::move(t)))
	    .first->second;
}

bool Database::hasRelation(std::string name) { return relations.find(name) != relations.end(); }

Relation& Database::operator[](std::string key) { return relations[key]; };

BlockRelation::Block BlockRelation::createBlock(size_t minNrElements) {
	auto elements = std::max(minBlockSize, minNrElements);
	auto a        = this_worker->allocator.allocate(sizeof(BlockHeader) + elements * currentAttributeSize);
	auto header   = new (a) BlockHeader(elements);
	{
		std::lock_guard<std::mutex> lock(insertMutex);
		blocks.push_back(header);
	}
	return Block(this, header);
}

BlockRelation::Attribute BlockRelation::addAttribute(std::string name, size_t elementSize) {
	Attribute attr = attributes.size();
	attributes.emplace_back(elementSize, currentAttributeSize);
	attributeNames.emplace(name, attr);
	currentAttributeSize += elementSize;
	return attr;
}

BlockRelation::~BlockRelation() {
	// Block storage is freed by queries own memory pool
	// Thus, no freeing needed here.
}
} // namespace runtime
