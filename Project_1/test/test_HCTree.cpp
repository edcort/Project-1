#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>

#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        freqs['c'] = 4;
        freqs['z'] = 100;

        tree.build(freqs);
    }
};

/*
class ASCIIExtended : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    ASCIIExtended() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs[(unsigned char)'¡'] = 2;
        freqs[(unsigned char)'¢'] = 3;
        freqs[(unsigned char)'£'] = 4;
        freqs[(unsigned char)'¤'] = 100;

        tree.build(freqs);
    }
};
*/

class FishFixture : public ::testing::Test {
  protected:
    HCTree fishTree;

  public:
    FishFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['h'] = 2;
        freqs['u'] = 9;
        freqs['m'] = 2;
        freqs['n'] = 2;
        freqs['k'] = 2;
        freqs['a'] = 3;
        freqs['p'] = 1;
        freqs['`'] = 1;

        fishTree.build(freqs);
    }
};

class basicExample : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    basicExample() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 1;
        freqs['b'] = 2;
        freqs['c'] = 5;
        freqs['d'] = 9;
        freqs['e'] = 18;
        freqs['f'] = 40;
        freqs['g'] = 80;
        freqs['h'] = 200;
        freqs['i'] = 400;

        tree.build(freqs);
    }
};

class singleNode : public ::testing::Test {
  protected:
    HCTree singleNodeTree;

  public:
    singleNode() {
        vector<unsigned int> freqs(256);
        freqs['!'] = 999;
        singleNodeTree.build(freqs);
    }
};

/* --------------------TESTIN ENCODING SINGLE NODE HUFFMAN TREE */
TEST_F(singleNode, SINGLE_NODE_TEST_1_ENCODE) {
    ostringstream os;
    singleNodeTree.encode('!', os);
    ASSERT_EQ(os.str(), "0");
}
/* ------------------------------------------------------------*/

/* ----------------------------TESTING DECODING ASCIIExtended HUFFMAN TREE */
/*
TEST_F(ASCIIExtended, ASCIIExtended_TEST_1_DECODE) {
    string stringvalues = "1";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, '¤');
}

TEST_F(ASCIIExtended, ASCIIExtended_TEST_2_DECODE) {
    string stringvalues = "010";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'a');
}

TEST_F(ASCIIExtended, ASCIIExtended_TEST_3_DECODE) {
    string stringvalues = "00";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'c');
}

TEST_F(ASCIIExtended, ASCIIExtended_TEST_4_DECODE) {
    string stringvalues = "0000101010111";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, '\0');
}
*/
/* -------------------------------------------------------------------*/

/*
/* -------------------- TESTIN ENCODING ASCIIExtended HUFFMAN TREE */
/*
TEST_F(ASCIIExtended, ASCIIExtended_1_ENCODE) {
    ostringstream os;
    tree.encode('¤', os);
    ASSERT_EQ(os.str(), "1");
}
TEST_F(ASCIIExtended, ASCIIExtended_2_ENCODE) {
    ostringstream os;
    tree.encode('£', os);
    ASSERT_EQ(os.str(), "00");
}
TEST_F(ASCIIExtended, ASCIIExtended_3_ENCODE) {
    ostringstream os;
    tree.encode('¢', os);
    ASSERT_EQ(os.str(), "011");
}
TEST_F(ASCIIExtended, ASCIIExtended_4_ENCODE) {
    ostringstream os;
    tree.encode('¡', os);
    ASSERT_EQ(os.str(), "010");
}
*/
/* -------------------------------------------------------------------------------*/

/* -------------------- TESTIN ENCODING BIT OUTPUT */

TEST_F(basicExample, NEW_TEST_1) {
    ostringstream os;
    BitOutputStream out(os);
    tree.encode('i', out);
    out.flush();
    ASSERT_EQ(os.str(), "\x80");
}

TEST_F(basicExample, NEW_TEST_2) {
    ostringstream os;
    BitOutputStream out(os);
    tree.encode('g', out);
    out.flush();
    ASSERT_EQ(os.str(), " ");
}
/* -------------------------------------------------------------------------------*/

/* -------------------- TESTIN ENCODING FISH HUFFMAN TREE */

TEST_F(FishFixture, FISH_TEST_1_ENCODE) {
    ostringstream os;
    fishTree.encode('h', os);
    ASSERT_EQ(os.str(), "100");
}
TEST_F(FishFixture, FISH_TEST_2_ENCODE) {
    ostringstream os;
    fishTree.encode('u', os);
    ASSERT_EQ(os.str(), "0");
}
TEST_F(FishFixture, FISH_TEST_3_ENCODE) {
    ostringstream os;
    fishTree.encode('m', os);
    ASSERT_EQ(os.str(), "1110");
}
TEST_F(FishFixture, FISHL_TEST_4_ENCODE) {
    ostringstream os;
    fishTree.encode('n', os);
    ASSERT_EQ(os.str(), "1101");
}
TEST_F(FishFixture, FISHL_TEST_5_ENCODE) {
    ostringstream os;
    fishTree.encode('k', os);
    ASSERT_EQ(os.str(), "1111");
}
TEST_F(FishFixture, FISHL_TEST_6_ENCODE) {
    ostringstream os;
    fishTree.encode('a', os);
    ASSERT_EQ(os.str(), "101");
}
TEST_F(FishFixture, FISHL_TEST_7_ENCODE) {
    ostringstream os;
    fishTree.encode('p', os);
    ASSERT_EQ(os.str(), "11000");
}
TEST_F(FishFixture, FISHL_TEST_8_ENCODE) {
    ostringstream os;
    fishTree.encode('`', os);
    ASSERT_EQ(os.str(), "11001");
}

/* -------------------------------------------------------------------------------*/

/* ----------------------------TESTING ENCODING SMALL HUFFMAN TREE */
TEST_F(SimpleHCTreeFixture, SMALL_TEST_1_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "010");
}
TEST_F(SimpleHCTreeFixture, SMALL_TEST_2_ENCODE) {
    ostringstream os;
    tree.encode('b', os);
    ASSERT_EQ(os.str(), "011");
}
TEST_F(SimpleHCTreeFixture, SMALL_TEST_3_ENCODE) {
    ostringstream os;
    tree.encode('c', os);
    ASSERT_EQ(os.str(), "00");
}
TEST_F(SimpleHCTreeFixture, SMALL_TEST_4_ENCODE) {
    ostringstream os;
    tree.encode('z', os);
    ASSERT_EQ(os.str(), "1");
}
/* -------------------------------------------------------------------*/

/*
 * TESTING HCNode comparator
 */
TEST(ALL_DIFF_FREQ, ComparatorTest) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(5, 'Y');
    HCNode* hcn2 = new HCNode(2, 'D');
    HCNode* hcn3 = new HCNode(4, 'O');
    HCNode* hcn4 = new HCNode(3, 'Q');
    HCNode* hcn5 = new HCNode(1, 'A');
    pq.push(hcn1);
    pq.push(hcn2);
    pq.push(hcn3);
    pq.push(hcn4);
    pq.push(hcn5);

    ASSERT_EQ(pq.top()->symbol, 'A');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'D');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'Q');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'O');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'Y');
    pq.pop();
    ASSERT_EQ(pq.size(), 0);
}

TEST(FISH_EXAMPLE_DiscussionVideo, ComparatorTest) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(2, 'h');
    HCNode* hcn2 = new HCNode(9, 'u');
    HCNode* hcn3 = new HCNode(2, 'm');
    HCNode* hcn4 = new HCNode(2, 'n');
    HCNode* hcn5 = new HCNode(2, 'k');
    HCNode* hcn6 = new HCNode(3, 'a');
    HCNode* hcn7 = new HCNode(1, 'p');
    HCNode* hcn8 = new HCNode(1, '`');
    pq.push(hcn1);
    pq.push(hcn2);
    pq.push(hcn3);
    pq.push(hcn4);
    pq.push(hcn5);
    pq.push(hcn6);
    pq.push(hcn7);
    pq.push(hcn8);

    ASSERT_EQ(pq.top()->symbol, 'p');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, '`');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'n');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'm');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'k');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'h');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'a');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'u');
    pq.pop();
    ASSERT_EQ(pq.size(), 0);
}

TEST(ALL_SAME_FREQ, ComparatorTest) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    HCNode* hcn1 = new HCNode(1, 'A');
    HCNode* hcn2 = new HCNode(1, 'K');
    HCNode* hcn3 = new HCNode(1, 'S');
    HCNode* hcn4 = new HCNode(1, 'W');
    HCNode* hcn5 = new HCNode(1, 'Y');
    HCNode* hcn6 = new HCNode(1, 'Z');
    HCNode* hcn7 = new HCNode(1, '[');
    HCNode* hcn8 = new HCNode(1, 'a');
    pq.push(hcn3);
    pq.push(hcn2);
    pq.push(hcn7);
    pq.push(hcn4);
    pq.push(hcn1);
    pq.push(hcn6);
    pq.push(hcn8);
    pq.push(hcn5);

    ASSERT_EQ(pq.top()->symbol, 'a');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, '[');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'Z');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'Y');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'W');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'S');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'K');
    pq.pop();
    ASSERT_EQ(pq.top()->symbol, 'A');
    pq.pop();
    ASSERT_EQ(pq.size(), 0);
}

/* ----------------------------TESTING DECODING SMALL HUFFMAN TREE */

TEST_F(SimpleHCTreeFixture, SMALL_TEST_1_DECODE) {
    string stringvalues = "1";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'z');
}

TEST_F(SimpleHCTreeFixture, SMALL_TEST_2_DECODE) {
    string stringvalues = "011";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'b');
}

TEST_F(SimpleHCTreeFixture, SMALL_TEST_3_DECODE) {
    string stringvalues = "010";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'a');
}

TEST_F(SimpleHCTreeFixture, SMALL_TEST_4_DECODE) {
    string stringvalues = "00";
    istringstream is(stringvalues);
    byte answer = tree.decode(is);
    ASSERT_EQ(answer, 'c');
}

/* -------------------- TESTIN DECODING BIT INPUT */

TEST_F(basicExample, DECODE_BIT_1) {
    string stringvalues = "\0";
    istringstream is(stringvalues);

    BitInputStream in(is);
    byte answer = tree.decode(in);

    ASSERT_EQ(answer, 'i');
}

/* -------------------------------------------------------------------------------*/

/* -------------------------------------------------------------------*/

/*
TEST(HCTree, DecodeTest) {
    // make it possible to create a HCTree without calling build
    // HCTree( HCNode* root)

    // create some HCNodes that are linked to each other
    // create HCTree using the root of our own tree

    // now we can call decode on that HCTree and assert that the right things
    // happened
}
*/