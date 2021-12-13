/**
 * TODO: file header
 *
 * Author:
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

class BitInputStream {
  private:
    // reference to the input stream to use
    istream& in;

    // one byte buffer of bits
    byte buf;

    // number of bits that have been writen to buf
    unsigned int nbits;

  public:
    // TODO: Initialize member variables.
    explicit BitInputStream(istream& is) : in(is) {
        nbits = 0;
        fill();
    };

    void fill();

    unsigned int readBit();
};

#endif