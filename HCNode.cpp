#ifndef HCNODE_CPP
#define HCNODE_CPP

#include <cassert>
#include "HCNode.hpp"

bool HCNode::operator<(const HCNode& other)
{
	if (this->count != other.count) {
		return this->count > other.count;
	}

	return this->symbol < other.symbol;
}

bool comp(HCNode* one, HCNode* other)
{
	assert(one != nullptr && other != nullptr);
	return *one < *other;
}


#endif // HCNODE_CPP
