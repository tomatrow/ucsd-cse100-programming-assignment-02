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

#endif // HCNODE_CPP
