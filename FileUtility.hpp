#ifndef FILEUTILITY_HPP
#define FILEUTILITY_HPP

#include <vector>
#include <fstream>

/** Does things with the file system.
* Serves streams and closes them.
* Diffs
* Gets frequencies sinces there is nowhere else to put it.
*/
class FileUtility
{
private:
	vector<int>* freqs;
	string fileName;
	ofstream* out;
	ifstream* in;

public:

	FileUtility(string fileName);
	~FileUtility();

	ofstream& outFileStream() const;
	ifstream& inFileStream() const;

	const vector<int> freqs() const;
	const string fileName() const;

	static bool different(string firstName, string secondName) const;
};

#endif // FILEUTILITY_HPP
