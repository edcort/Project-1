#include "BitInputStream.hpp"

// TODO: Fill the buffer from the input stream.
void BitInputStream::fill() {
    // reads in a byte from the input stream
    // and stores it into our buffer varaible
    buf = in.get();
    nbits = 0;
}

// TODO: Read the next bit from the buffer.
unsigned int BitInputStream::readBit() {
    unsigned int pos_to_return = 0;
    unsigned int pos_val = 0;

    if (nbits < 8) {
        // pos_val contain the position we want to output
        // and we shif it to the leftmost side and do
        // bitwise operation &1

        // if the last bit is 1 then we return 1
        // if the last bit is 0 then we return 0
        pos_val = 7 - nbits;
        pos_to_return = ((buf >> pos_val) & 1);

        nbits++;
        return pos_to_return;
    } else {
        fill();

        pos_val = 7 - nbits;
        pos_to_return = ((buf >> pos_val) & 1);

        nbits++;

        return pos_to_return;
    }
}
