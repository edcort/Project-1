/**
 * TODO: file header
 *
 * Author: Eduardo Cortez
 */
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(const string& inFileName, const string& outFileName) {
    vector<unsigned int> freqs(256);

    unsigned char char_val;
    int temp;
    ifstream in_file;
    ofstream out_file;
    out_file.open(outFileName, ios::binary);
    in_file.open(inFileName, ios::binary);

    // add all the frequency counts of each of the 256 ASCII chars into freqs
    while (in_file.peek() != -1) {
        temp = in_file.get();
        freqs[temp] = freqs.at(temp) + 1;
    }

    // output to the outfile the naive header (256 line of the frequency counts)
    for (int i = 0; i < freqs.size(); i++) {
        out_file << freqs[i] << endl;
    }

    // close file we are seeking to compress
    in_file.close();

    // reopen file we are seeking to compress
    // (in order to refresh get() to the start of the file again)
    in_file.open(inFileName, ios::binary);

    HCTree arbol;
    arbol.build(freqs);

    while (in_file.peek() != -1) {
        temp = in_file.get();
        char_val = (unsigned char)(temp);
        arbol.encode(char_val, out_file);
    }

    out_file.close();
    in_file.close();
}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(const string& inFileName, const string& outFileName) {
    vector<unsigned int> freqs(256);

    ifstream in_file;
    ofstream out_file;
    out_file.open(outFileName, ios::binary);
    in_file.open(inFileName, ios::binary);

    unsigned char char_val;
    int temp;

    // unsigned long total_freq_count;

    // add all the frequency counts of each of the 256 ASCII chars into freqs
    while (in_file.peek() != -1) {
        temp = in_file.get();
        freqs[temp] = freqs.at(temp) + 1;
    }

    // output to the outfile the naive header (256 line of the frequency counts)
    for (int i = 0; i < freqs.size(); i++) {
        out_file << freqs[i] << endl;
    }

    // close file we are seeking to compress
    in_file.close();

    // reopen file we are seeking to compress
    // (in order to refresh get() to the start of the file again)
    in_file.open(inFileName, ios::binary);

    HCTree arbol;
    arbol.build(freqs);
    BitOutputStream out = BitOutputStream(out_file);

    while (in_file.peek() != -1) {
        temp = in_file.get();
        char_val = (unsigned char)(temp);
        arbol.encode(char_val, out);
    }

    out.flush();

    out_file.close();
    in_file.close();
}

/* Main program that runs the compression */
int main(int argc, char* argv[]) {
    cxxopts::Options options(argv[0],
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        return 0;
    }

    // if original file is empty, output empty file
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName, ios::out);
        outFile.close();
        return 0;
    }

    if (isAsciiOutput) {
        pseudoCompression(inFileName, outFileName);
    } else {
        trueCompression(inFileName, outFileName);
    }

    return 0;
}