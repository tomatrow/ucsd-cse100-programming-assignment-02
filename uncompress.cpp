#ifndef UNCOMPRESS_CPP
#define UNCOMPRESS_CPP

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include "HCTree.hpp"
#include "FileUtility.hpp"

int main(int argc, char* argv[]) {
	// cout << "Hello World!!! (uncompress)" << endl;
	assert(argc == 3); // path original destination

	FileUtility utility(argv[1], argv[2]);
	vector<int> freq(256);
	HCTree::decodeHeader(utility.inFileStream(), freq);
	HCTree tree;
	tree.build(freq);
	tree.decodeFile(utility.inFileStream(), utility.outFileStream());

	return 0;
}

#endif // UNCOMPRESS_CPP
