#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** A 'function class' for use as the Compare class in a
 *  priority_queue<HCNode*>.
 *  For this to work, operator< must be defined to
 *  do the right thing on HCNodes.
 */
class HCNodePtrComp {
public:
    bool operator()(HCNode*& lhs, HCNode*& rhs) const {
        return *lhs < *rhs;
    }
};

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class HCTree {
    friend int testTree();

private:
    HCNode* root;
    vector<HCNode*> leaves;

public:
    explicit HCTree() : root(nullptr) {
        leaves = vector<HCNode*>(256, (HCNode*) nullptr);
    }

    ~HCTree();

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void build(const vector<int>& freqs);


    // MARK - Encoding


    /// Reads the distribution of any text file.
    static void frequencies(ifstream& in, vector<int>& vec);]

    /** Encode in and writes it to out.
     * Effectivly calls encodeFile() and encodeHeader()
     */
    void encodeFile(ifstream& in, ofstream& out) const;

    /** Write the headers to the given stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encodeHeader(ofstream& out) const;

    /** Encodes the main message. Fails of tree is not buildt.
     */
    void encodeBody(ifstream& in, ofstream& out) const;

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encodeSymbol(byte symbol, BitOutputStream& out) const;

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void encodeSymbol(byte symbol, ofstream& out) const;


    // MARK - Decoding


    /// Decodes an encoded header.
    static int decodeHeader(ifstream& in, vector<int>& vec);

    /** Reads from in and writes to out.
     */
    void decodeFile(ifstream& in, ofstream& out) const;

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decodeSymbol(BitInputStream& in) const;

    /** Return the symbol coded in the next sequence of bits (represented as
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int decodeSymbol(ifstream& in) const;

};

#endif // HCTREE_HPP
