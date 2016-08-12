#ifndef COMPRESS_CPP
#define COMPRESS_CPP

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include "HCTree.hpp"
#include "FileUtility.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	// cout << "Hello World!!! (compress)" << endl;

	assert(argc == 3); // path original destination

	FileUtility utility(argv[1], argv[2]);
	vector<int> freq(256);
	HCTree::frequencies(utility.inFileStream(), freq);

	// that edge case
	bool allZero = true;
	for (auto x : freq)
	{
		if (x > 0)
		{
			allZero = false;
		}
	}
	if (allZero)
	{
		for (auto x : freq)
		{
			utility.outFileStream() << x << endl;
		}
		return 0;
	}

	HCTree tree;
	tree.build(freq);
	tree.encode(utility.inFileStream(), utility.outFileStream());

	return 0;
}

#endif // COMPRESS_CPP
