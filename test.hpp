#ifndef TEST_HPP
#define TEST_HPP

#include <string>

using namespace std;

int main(int argc, char const *argv[]);

/**
* For both checkpoint1.txt and checkpoint2.txt
*   Calls compress
*   calls uncompress
*   Diff's between original.
*/
void checkPointTest(string location);

#endif // TEST_HPP
