#include "BitOutputStream.hpp"

/**
 * TODO: Write the buffer to the output stream,
 * and then clear the buffer to allow further use.
 * You may use std::fill() to zero-fill the buffer.
 *
 * Note: don’t flush the ostream here, as it is an extremely slow operation that
 * may cause a timeout.
 */
void BitOutputStream::flush() {
    out.put(buf);
    nbits = 0;
    buf = 0;
    // out.flush();
}

/**
 * TODO: Write the least significant bit of the given int to the bit buffer.
 * Flushes the buffer first if it is full (which means all the bits in the
 * buffer have already been set). You may assume the given int is either 0 or 1.
 */
void BitOutputStream::writeBit(unsigned int i) {
    int pos_to_add_i = 0;

    if (nbits < 8) {
        // contains LSB in the location it should be added to buffer
        pos_to_add_i = (i << (7 - nbits));

        // insert LSB to the available slot in buf
        buf = (buf | pos_to_add_i);

        nbits++;

        // cout << "hi" << endl;

    } else {
        flush();

        // contains LSB in the location it should be added to buffer
        pos_to_add_i = (i << (7 - nbits));

        // insert LSB to the available slot in buf
        buf = (buf | pos_to_add_i);

        nbits++;
    }
}
