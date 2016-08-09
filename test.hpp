#ifndef TEST_HPP
#define TEST_HPP

#include <string>
#include <vector>
#include "HCNode.hpp"

using namespace std;

int main(int argc, char const *argv[]);

int testNode();
int testTree();

vector<int> frequenciesInFile(string fileName);
vector<int> frequenciesInString(string s);
void postorder(HCNode* root, int indent);
void inorder(HCNode * root, vector<HCNode*> *vec);


#endif // TEST_HPP
