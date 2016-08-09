#ifndef HCTREE_CPP
#define HCTREE_CPP

#include "HCTree.hpp"
#include <queue>
#include <cassert>
#include <algorithm>
#include <iostream>



HCTree::~HCTree()
{
// TODO
}

void HCTree::build(const vector<int>& freqs)
{
	assert(freqs.size() == 256);

	priority_queue< HCNode*, vector<HCNode*>, HCNodePtrComp > queue;

	// prepare for linking
	for (int i = 0; i < freqs.size(); i++)
	{
		this->leaves[i] = new HCNode(freqs[i], i);
		if (this->leaves[i]->count > 0)
		{
			queue.push(this->leaves[i]);
		}
	}


	// Make the links
	while (queue.size() >= 2)
	{
		// pop off
		auto greater = queue.top();
		queue.pop();
		auto lesser = queue.top();
		queue.pop();

		// cout << "Greater: " << *greater << endl;
		// cout << "Lesser: " << *lesser << endl;

		// build triangle tree
		auto biggerSymbol = max(lesser->symbol, greater->symbol);
		auto sum = greater->count + lesser->count;
		auto node = new HCNode(sum, biggerSymbol);

		// Want children to be ordered by symbol from left to right.
		if (greater->symbol == biggerSymbol)
		{
			node->c0 = lesser;
			node->c1 = greater;
		}
		else
		{
			node->c0 = greater;
			node->c1 = lesser;
		}
		assert(node->c0->symbol < node->c1->symbol);

		greater->p = node;
		lesser->p = node;

		// add the new dummy back
		queue.push(node);

		// cout << "Node: " << *node << endl;
	}

	this->root = queue.top();
	queue.pop();

	assert(queue.empty());

}

#endif // HCTREE_CPP
