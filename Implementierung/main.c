#include <stdio.h>
#include <stdlib.h>

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
const char *HELP_MSG = "\nusage: huffman <input_file> [-V version_num] [-B n] [-d] [-o output_file] [-h]\n\n"
                       "\tinput_file: Path to input file used for Huffman en-/decoding\n\n"
                       "\t-V <version_num>: Implementation version to use (as number, default: 0)\n"
                       "\t-B <n>: Time measurement over n rounds (as number)\n"
                       "\t-d: If set decrypting given Huffman code\n"
                       "\t-o <output_file>: Output file to write result into\n"
                       "\t-h: Shows this help menu\n\n";

/**
 * @brief Prints help message if arguments not valid (or -h was used)
 */
void print_help() {
    fprintf(stderr, "%s", HELP_MSG);
}

// Main method executed with program start
int main(int argc, char **argv) {

    // Checking if program and arguments valid
    if (argc <= 1) {
        print_help();
        return EXIT_FAILURE;
    }

    return 0;
}