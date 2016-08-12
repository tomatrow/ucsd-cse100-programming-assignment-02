#ifndef FILEUTILITY_HPP
#define FILEUTILITY_HPP

#include <vector>
#include <fstream>
#include <string>

using namespace std;

/** Does things with the file system.
* Serves streams and closes them.
*/
class FileUtility
{

private:
	const string _inFileName;
	const string _outFileName;

	ifstream* _in;
	ofstream* _out;

public:

	/** The only constructor.
	 *  Opens the infile and makes sure it's readable and non-empty.
	 *  Makes sure outfile does NOT exist.
	 */
	FileUtility(const string & inFileName, const string & outFileName);

	/** The deconstructor.
	 * Closes streams.
	 * Deletes pointers.
	 */
	~FileUtility();

	// The all important streams.
	ifstream& inFileStream() const;
	ofstream& outFileStream() const;

	// getters
	const string inFileName() const;
	const string outFileName() const;
};

#endif // FILEUTILITY_HPP
