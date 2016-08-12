#ifndef FILEUTILITY_CPP
#define FILEUTILITY_CPP

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
// #include <fstream>
#include "FileUtility.hpp"

using namespace std;

FileUtility::FileUtility(const string & inFileName, const string & outFileName) : _inFileName(inFileName), _outFileName(outFileName)
{
	//Open file
	_in = new ifstream();
	_in->open(_inFileName, ios::binary);

	//Check if input file was actually opened
	if(!_in->is_open())
	{
		cout << "Invalid input file. No file was opened. Please try again.\n";
		assert(false);
	}

	//Check for empty file
	_in->seekg(0, ios_base::end);
	unsigned int len = _in->tellg();
	if (len == 0)
	{
		// cout << "The file is empty. \n";
		// assert(false);
	}

	//Resets the stream to beginning of file
	_in->seekg(0, ios_base::beg);

	// Make sure out file does not exist
	ifstream potentialOutFile(_outFileName);
    assert(!potentialOutFile.good());

	// create an open
	_out = new ofstream();
	_out->open(_outFileName, ios::binary);
	assert(_out->is_open());
}

FileUtility::~FileUtility()
{
	if (_in->is_open())
	{
		_in->close();
	}
	delete(_in);

	if (_out->is_open())
	{
		_out->close();
	}
	delete(_out);
}

ifstream& FileUtility::inFileStream() const
{
	return *_in;
}
ofstream& FileUtility::outFileStream() const
{
	return *_out;
}

#endif // FILEUTILITY_CPP
