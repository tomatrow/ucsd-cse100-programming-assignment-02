#ifndef HCTREE_CPP
#define HCTREE_CPP

#include "HCTree.hpp"
#include <queue>
#include <cassert>
#include <algorithm>
#include <iostream>


static void deleteAll(HCNode* n);


HCTree::~HCTree()
{
	// remove the fake nodes
	deleteAll(root);
	// remove the leaves
	for (auto p : leaves)
	{
		if (p != nullptr)
		{
			delete(p);
		}
	}
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

void HCTree::encode(byte symbol, ofstream& out) const
{
	assert(root != nullptr); // Build was called.

	auto leaf = leaves[symbol];
	string code = "";

	while (leaf->p != nullptr)
	{
		if (leaf->p->c0->symbol == leaf->symbol)
		{
			code = "0" + code;
		}
		else
		{
			code = "1" + code;
		}

		leaf = leaf->p;
	}

	out << code;
}

void HCTree::encodeHeader(ofstream& out) const
{
	assert(root != nullptr);
	for (auto node : leaves)
	{
		out << node->count << "\n";
	}
}

void HCTree::encodeBody(ifstream& in, ofstream& out) const
{
	assert(root != nullptr);
	while (true) {
		byte c = in.get();
		// explained in the slides.
		// Apperently, eof is reached by reading PAST the file.
		if (in.eof())
		{
			break;
		}
		encode(c, out);
	}
}

void HCTree::frequencies(ifstream& in, vector<int>& vec)
{
	assert(vec.size() == 256);
	while (true) {
		char c = in.get();
		// explained in the slides.
		// Apperently, eof is reached by reading PAST the file.
		if (in.eof())
		{
			break;
		}
		vec[c]++;
	}

	//Resets the stream to beginning of file
	in.clear();
	in.seekg(0, ios_base::beg);
}

void HCTree::encode(ifstream& in, ofstream& out) const
{
	assert(root != nullptr);
	// reset stream
	in.clear();
	in.seekg(0, ios_base::beg);

	encodeHeader(out);
	encodeBody(in, out);
}

int HCTree::decodeHeader(ifstream& in, vector<int>& vec)
{
	assert(vec.size() == 256);
	for (int i = 0; i < vec.size(); i++)
	{
		string line;
		getline(in, line);
		vec[i] = stoul(line);
	}

	return in.tellg();
}

void HCTree::decode(ifstream& in, ofstream& out) const
{
	assert(root != nullptr);
	// reset stream
	// in.clear();
	// in.seekg(0, ios_base::beg);
	while (true) {
		byte c = in.peek();
		if (c == '0' || c == '1')
		{
			out << (byte) decode(in);;
		}
		if (in.eof())
		{
			break;
		}
	}

}


int HCTree::decode(ifstream& in) const
{
	assert(root != nullptr);
	// assume the stream isnt empty
	// assome it's all 0's, 1's
	auto current = root;
	while (current->c0 != nullptr || current->c1 != nullptr)
	{
		byte c = in.get();
		assert(c == '0' || c == '1');

		if (c == '0')
		{
			current = current->c0;
		}
		else
		{
			current = current->c1;
		}
	}

	return current->symbol;
}


/** postorder traversal, deleting nodes
*/
static void deleteAll(HCNode* n) {
	/* Pseudo Code:
	  if current node is null: return;
	  recursively delete left sub-tree
	  recursively delete right sub-tree
	  delete current node
	*/

	if (n == nullptr)
	{
		return;
	}
	if (n->c0 == nullptr && n->c1 == nullptr) {// leave the leaves for later
		return;
	}
	deleteAll(n->c0);
	deleteAll(n->c1);
	delete(n);
	n = 0;
}


#endif // HCTREE_CPP
