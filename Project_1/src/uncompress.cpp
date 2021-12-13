/**
 * TODO: file header
 *
 * Author:
 */
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(const string& inFileName, const string& outFileName) {
    vector<unsigned int> freqs(256);
    unsigned int size_header = 256;
    int string_to_int_val;
    string string_val;

    ifstream in_file;
    ofstream out_file;

    out_file.open(outFileName, ios::binary);
    in_file.open(inFileName, ios::binary);

    // read the naive header file and populate the frequency count appropriately
    // in freqs
    unsigned long total_freq = 0;

    int i = 0;
    while (i < size_header) {
        getline(in_file, string_val);
        string_to_int_val = stoi(string_val, nullptr, 10);
        freqs[i] = string_to_int_val;
        total_freq = total_freq + string_to_int_val;
        i++;
    }

    HCTree arbol;
    arbol.build(freqs);

    unsigned long code_count = 0;
    byte output_symbol;

    while (code_count < total_freq) {
        output_symbol = arbol.decode(in_file);
        out_file << output_symbol;

        code_count++;
    }

    out_file.close();
    in_file.close();
}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(const string& inFileName, const string& outFileName) {
    vector<unsigned int> freqs(256);
    unsigned int size_header = 256;
    int string_to_int_val;
    string string_val;

    ifstream in_file;
    ofstream out_file;

    out_file.open(outFileName, ios::binary);
    in_file.open(inFileName, ios::binary);

    // read the naive header file and populate the frequency count appropriately
    // in freqs
    unsigned long total_freq = 0;

    int i = 0;
    while (i < size_header) {
        getline(in_file, string_val);
        string_to_int_val = stoi(string_val, nullptr, 10);
        freqs[i] = string_to_int_val;
        total_freq = total_freq + string_to_int_val;
        i++;
    }

    HCTree arbol;
    arbol.build(freqs);

    BitInputStream in = BitInputStream(in_file);

    unsigned long code_count = 0;
    byte output_symbol;

    while (code_count < total_freq) {
        output_symbol = arbol.decode(in);
        out_file << output_symbol;

        code_count++;
    }

    out_file.close();
    in_file.close();
}

/* Main program that runs the decompression */
int main(int argc, char* argv[]) {
    cxxopts::Options options(argv[0],
                             "Uncompresses files using Huffman Encoding");
    options.positional_help(
        "./path_to_compressed_input_file ./path_to_output_file");

    bool isAscii = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Read input in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAscii))("input", "",
                                       cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit.");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }

    // if compressed file is empty, output empty file
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream outFile;
        outFile.open(outFileName, ios::out);
        outFile.close();
        exit(0);
    }

    if (isAscii) {
        pseudoDecompression(inFileName, outFileName);
    } else {
        trueDecompression(inFileName, outFileName);
    }

    return 0;
}
