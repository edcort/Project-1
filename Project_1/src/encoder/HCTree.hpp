#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

class HCTree {
  private:
    // the root of HCTree
    HCNode* root;

    // a vector storing pointers to all leaf HCNodes
    vector<HCNode*> leaves;

  public:
    /* TODO: Initializes a new empty HCTree.*/
    HCTree() : root(0) {
        unsigned int i = 0;
        while (i != 256) {
            leaves.push_back((HCNode*)(0));
            i++;
        }
    }

    ~HCTree();

    void build(const vector<unsigned int>& freqs);

    void encode(byte symbol, BitOutputStream& out) const;

    void encode(byte symbol, ostream& out) const;

    byte decode(BitInputStream& in) const;

    // Approach 1st (Recommendation)
    byte decode(istream& in) const;

    // HELPER METHOD
    void clear_helper(HCNode* curr);
};

#endif  // HCTREE_HPP
