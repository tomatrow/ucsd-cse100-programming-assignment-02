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
	HCTree tree;
	tree.build(freq);
	tree.encode(utility.inFileStream(), utility.outFileStream());

	return 0;
}

#endif // COMPRESS_CPP
