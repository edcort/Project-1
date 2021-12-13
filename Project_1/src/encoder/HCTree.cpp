#include "HCTree.hpp"

/* TODO: Delete all objects on the heap to avoid memory leaks. */
HCTree::~HCTree() { clear_helper(root); }  // destructor D: !!!

/**
 * TODO: Build the HCTree from the given frequency vector. You can assume the
 * vector must have size 256 and each value at index i represents the frequency
 * of char with ASCII value i. Only non-zero frequency symbols should be used to
 * build the tree. The leaves vector must be updated so that it can be used in
 * encode() to improve performance.
 *
 * When building the HCTree, you should use the following tie-breaking rules to
 * match the output from reference solution in checkpoint:
 *
 *    1. HCNode with lower count should have higher priority. If count is the
 * same, then HCNode with a larger ascii value symbol should have higher
 * priority. (This should be already defined properly in the comparator in
 * HCNode.hpp)
 *    2. When popping two highest priority nodes from PQ, the higher priority
 * node will be the ‘c0’ child of the new parent HCNode.
 *    3. The symbol of any parent node should be taken from its 'c0' child.
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    // create a priority queue incorporating the comparator we designed
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    // create all HCNodes appropriately according to the info provided
    // from freqs and add to pq and updates leaves accordingly
    for (unsigned int i = 0; i < freqs.size(); i++) {
        // consider only non-zero frequency symbols
        if (freqs.at(i) > 0) {
            HCNode* addMe = new HCNode(freqs.at(i), (unsigned char)(i));
            pq.push(addMe);
            leaves.at(i) = addMe;
        }
    }

    if (pq.size() == 1) {
        HCNode* temp = pq.top();
        pq.pop();

        HCNode* curr = new HCNode(temp->count, temp->symbol);
        root = curr;

        root->c0 = temp;
        temp->p = root;
    } else {
        // continue while we have 2 or more nodes in our pq
        while (pq.size() > 1) {
            // attain the first two nodes in the pq
            HCNode* first = pq.top();
            pq.pop();
            HCNode* second = pq.top();
            pq.pop();

            // appropriatly set the parent to the stated rules
            HCNode* parent =
                new HCNode(first->count + second->count, first->symbol);
            parent->c0 = first;
            parent->c1 = second;
            first->p = parent;
            second->p = parent;

            // push the new parent onto the pq
            pq.push(parent);
        }

        // set the single node from the pq to the root
        root = pq.top();
        pq.pop();
    }
}

/**
 * TODO: Write the encoding bits of the given symbol to the ostream. You should
 * write each encoding bit as ascii char either '0' or '1' to the ostream. You
 * must not perform a comprehensive search to find the encoding bits of the
 * given symbol, and you should use the leaves vector instead to achieve
 * efficient encoding. For this function to work, build() must be called before
 * to create the HCTree.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    HCNode* node = leaves.at((unsigned int)symbol);

    stack<char*> encode_info;
    HCNode* curr = node;

    char z = '0';
    char* zero = &z;
    char o = '1';
    char* one = &o;

    string encoded_string = "";

    if (root->c0 == node) {
        encoded_string = encoded_string + "0";
    } else if (root->c1 == node) {
        encoded_string = encoded_string + "1";
    } else {
        HCNode* par = node->p;

        while (curr != root) {
            par = curr->p;

            if (par->c0 == curr) {
                encoded_string = "0" + encoded_string;
            } else {
                encoded_string = "1" + encoded_string;
            }

            curr = curr->p;
        }
    }

    for (unsigned int i = 0; i < encoded_string.size(); i++) {
        if (encoded_string[i] == '0') {
            out.writeBit(0);
        } else {
            out.writeBit(1);
        }
    }
}

/**
 * TODO: Write the encoding bits of the given symbol to ostream. You should
 * write each encoding bit as ascii char either '0' or '1' to the ostream. You
 * must not perform a comprehensive search to find the encoding bits of the
 * given symbol, and you should use the leaves vector instead to achieve
 * efficient encoding. For this function to work, build() must have been called
 * beforehand to create the HCTree.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    HCNode* node = leaves.at((unsigned int)symbol);

    stack<char*> encode_info;
    HCNode* curr = node;

    char z = '0';
    char* zero = &z;
    char o = '1';
    char* one = &o;

    if (root->c0 == node) {
        encode_info.push(one);
        out.write("0", 1);
    } else if (root->c1 == node) {
        encode_info.push(one);
        out.write(one, 1);
    } else {
        HCNode* par = node->p;

        while (curr != root) {
            par = curr->p;

            if (par->c0 == curr) {
                encode_info.push(zero);
            } else {
                encode_info.push(one);
            }

            curr = curr->p;
        }

        while (encode_info.size() != 0) {
            out.write(encode_info.top(), 1);
            encode_info.pop();
        }
    }
}

/**
 * TODO: Decode the sequence of bits (represented as a char of either '0' or
 * '1') from the istream to return the coded symbol. For this function to work,
 * build() must have been called beforehand to create the HCTree.
 */
byte HCTree::decode(BitInputStream& in) const {
    if (root->c0 != nullptr && root->c1 == nullptr) {
        return root->c0->symbol;
    }

    HCNode* currNode = root;
    unsigned int curr_bit;

    while (currNode->c0 != nullptr && currNode->c1 != nullptr) {
        curr_bit = in.readBit();

        if (curr_bit == 0) {
            currNode = currNode->c0;
        }

        else if (curr_bit == 1) {
            currNode = currNode->c1;
        }
    }

    return currNode->symbol;
}

/**
 * TODO: Decode the sequence of bits (represented as char of either '0' or '1')
 * from istream to return the coded symbol. For this function to work, build()
 * must have been called beforehand to create the HCTree.
 */
byte HCTree::decode(istream& in) const {
    if (root->c0 != nullptr && root->c1 == nullptr) {
        return root->c0->symbol;
    }

    // KEEP !!!!!
    HCNode* currNode = root;
    char curr_bit;

    while (currNode->c0 != nullptr && currNode->c1 != nullptr) {
        in.get(curr_bit);

        if (curr_bit == '0') {
            currNode = currNode->c0;
        }

        else if (curr_bit == '1') {
            currNode = currNode->c1;
        }
    }
    return currNode->symbol;
}

// HELPER METHODs
void HCTree::clear_helper(HCNode* curr) {
    // if curr is null there is nothing to do
    if (curr == nullptr) {
        return;
    }

    // preserve memory address of the right child of curr before we delte curr
    HCNode* temp = curr->c1;

    // if curr has left child recursively call on it
    if (curr->c0 != nullptr) {
        clear_helper(curr->c0);
    }

    // delete curr
    delete curr;

    // if the right child is not null then recursively call on it
    if (temp != nullptr) {
        clear_helper(temp);
    }
}