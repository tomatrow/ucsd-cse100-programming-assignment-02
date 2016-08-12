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


void testOrder(HCNode* root, vector<HCNode*> leaves, string expected);
void treePlayground(HCTree tree);
HCTree* treeFromFile(string fileName);
void testFileUtility();

int main(int argc, char const* argv[]) {
	cout << "Hello World!!!" << endl;

	testNode();
	testTree();
	testFileUtility();

	return 0;
}

void testFileUtility()
{
	string original  = "testInput/checkpoint1.txt";
	string compressed = original + ".compressed";
	string uncompressed = original + ".uncompressed";

	FileUtility utility(compressed, compressed);
}

/** Tests the tree.
* We lok at a simple string.
* Then checkpoint1.txt and checkpoint2.txt
*/
int testTree()
{
	// Test Checkpoints
	string dir = "/Users/ajcaldwell/Dropbox/School/17/Summer2017/CSE100/pa02/working/testInput/";
	HCTree tree;

	// Checkpoint 1
	tree = *treeFromFile(dir + "checkpoint1.txt");
	testOrder(tree.root, tree.leaves, "abbdcdd");

	// Checkpoint 2
	tree = *treeFromFile(dir + "checkpoint2.txt");
	testOrder(tree.root, tree.leaves, "abbccdd");

	return 0;
}




void treePlayground(HCTree tree)
{
	ofstream s;

	cout << "a";
	tree.encodeSymbol((byte)'a', s);
	cout << "b";
	tree.encodeSymbol((byte)'b', s);
	cout << "c";
	tree.encodeSymbol((byte)'c', s);
	cout << "d";
	tree.encodeSymbol((byte)'d', s);
}

HCTree* treeFromFile(string fileName)
{
	auto tree = new HCTree();
	auto freqs = frequenciesInFile(fileName);
	tree->build(freqs);
	return tree;
}

void testOrder(HCNode* root, vector<HCNode*> leaves, string expected)
{
	auto inorderVec = new vector<HCNode*>();
	inorder(root, inorderVec);

	for (int i = 0; i < expected.length(); i++)
	{
		// cout << expected[i] << endl;
		// cout << (*inorderVec)[i]->symbol << endl;

		assert(expected[i] == (*inorderVec)[i]->symbol);
	}
}

void printFreq(vector<int> vec)
{
	for (int i = 0;i < vec.size();i++)
	{
		if (vec[i] > 0)
		{
			cout << (char)i << "," << vec[i] << "\n";
		}
	}
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

	// Close it up
	if (in.is_open())
	{
		in.close();
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
