#ifndef TEST_CPP
#define TEST_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include "test.hpp"
#include "FileUtility.hpp"
#include "HCTree.hpp"


using namespace std;

int main(int argc, char const* argv[]) {
	cout << "Hello World!!!" << endl;

	testNode();
	testTree();

	return 0;
}

/** Tests the tree.
* We lok at a simple string.
* Then checkpoint1.txt and checkpoint2.txt
*/
int testTree()
{

	// Test Tree for building.
	/*
	    C
	  A   C
	     B C
	*/
	auto tree = HCTree();
	string testString = "AABABC";
	auto freqs = frequenciesInString(testString);
	// for (int i = 0;i < freqs.size();i++)
	// {
	// 	if (freqs[i] > 0)
	// 	{
	// 		cout << i << "," << freqs[i] << "\n";
	// 	}
	// }
	tree.build(freqs);
	// for (auto n : tree.leaves)
	// {
	// 	if (n->p != nullptr)
	// 	{
	// 		cout << *n->p << "\n";
	// 	}
	// }
	// cout << "end" << endl;

	// cout << (char)tree.root->symbol << "\n";
	// cout << (char)tree.root->c0->symbol << "\n";
	// cout << (char)tree.root->c1->symbol << "\n";
	assert(tree.root->p == nullptr);
	assert(tree.root->symbol == 'C');
	assert(tree.root->c0 != nullptr);
	assert(tree.root->c0->symbol == 'A');
	assert(tree.root->c0->p == tree.root);
	assert(tree.root->c0->c0 == nullptr);
	assert(tree.root->c0->c1 == nullptr);
	assert(tree.root->c1->symbol == 'C');
	assert(tree.root->c1->c0->symbol == 'B');
	assert(tree.root->c1->c1->symbol == 'C');

	// Test Checkpoints
	string dir = "/Users/ajcaldwell/Dropbox/School/17/Summer2017/CSE100/pa02/working/testInput/";

	// Checkpoint 1
	// It's "abcd" repeated ten times.
	tree = HCTree();
	string one = dir + "checkpoint1.txt";
	freqs = frequenciesInFile(one);
	tree.build(freqs);

	// assert(false);

	string expectedInOrder = "abbdcdd";
	auto inorderVec = new vector<HCNode*>();
	inorder(tree.root, inorderVec);
	for (int i = 0; i < expectedInOrder.length(); i++)
	{
		// cout << expectedInOrder[i] << endl;
		// cout << (*inorderVec)[i]->symbol << endl;

		assert(expectedInOrder[i] == (*inorderVec)[i]->symbol);
	}

	return 0;
}

int testNode()
{
	auto n1 = new HCNode(1, '1');
	auto n2 = new HCNode(1, '2');
	auto n3 = new HCNode(2,'3');

	// Smaller the count, the greater the node
	assert(*n1 < *n2);
	assert(*n1 < *n2);
	assert(!(*n2 < *n1));
	assert(*n3 < *n2);
	assert(*n3 < *n1);

	return 0;
}

// helpers
vector<int> frequenciesInString(string s)
{
	vector<int> freqs(256);

	for (auto c : s)
	{
		// cout << c << "\n";
		freqs[c]++;
	}

	return freqs;
}

vector<int> frequenciesInFile(string fileName)
{
	//Open file
	ifstream in;
	in.open(fileName, ios::binary);

	//Check if input file was actually opened
	if(!in.is_open())
	{
		cout << "Invalid input file. No file was opened. Please try again.\n";
		assert(false);
	}

	//Check for empty file
	in.seekg(0, ios_base::end);
	unsigned int len = in.tellg();
	if (len == 0)
	{
		cout << "The file is empty. \n";
		assert(false);
	}

	//Resets the stream to beginning of file
	in.seekg(0, ios_base::beg);
	vector<int> freqs(256);
	while (true) {
		char c = in.get();
		// explained in the slides.
		// Apperently, eof is reached by reading PAST the file.
		if (in.eof())
		{
			break;
		}
		freqs[c]++;
	}

	return freqs;
}

void postorder(HCNode* root, int indent)
{
    if(root != nullptr) {
        if(root->c0) postorder(root->c0, indent+4);
        if(root->c1) postorder(root->c1, indent+4);
        if (indent) {
            cout << setw(indent) << ' ';
        }
        cout<< root->symbol << "\n ";
    }
}

void inorder(HCNode * root, vector<HCNode*> *vec)
{
	if (root == nullptr)
	{
		return;
	}
	inorder(root->c0, vec);
	vec->push_back(root);
	// cout << root << "[" << root->c0 << " : " << root->c1 << "]" << "\n";
	inorder(root->c1, vec);
}


#endif // TEST_CPP
