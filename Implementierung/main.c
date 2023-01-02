#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include "huffman.c"
#include "input_output.c"

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
const char *HELP_MSG = "\nusage: huffman <input_file> [-V version_num] [-B n] [-d] [-o output_file] [-h]\n\n"
                       "\tinput_file:\t\tPath to input file used for Huffman en-/decoding\n\n"
                       "\t-V <version_num>:\tImplementation version to use (as number, default: 0)\n"
                       "\t-B <n>:\t\t\tTime measurement over n rounds (as number)\n"
                       "\t-d:\t\t\tIf set decrypting given Huffman code\n"
                       "\t-o <output_file>:\tOutput file to write result into\n"
                       "\t-h:\t\t\tShows this help menu\n\n";

/**
 * @brief Prints help message if arguments not valid (or -h was used)
 */
void print_help() {
    perror(HELP_MSG);
}

int main(int argc, char **argv) {

    // Checking if program and arguments are valid
    if (argc < 2) {
        print_help();
        return EXIT_FAILURE;
    }

    int impl_num = 0;
    bool measure = false;
    int measure_rounds = 0;
    char *input_file;
    bool decrypt = false;
    char *output_file;

    // --help for -h
    static struct option help_synonym[] = {
            {"help", no_argument, NULL, 'h'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "V:B:o:dh", help_synonym, NULL)) != -1) {
        switch(opt) {
            case 'V':
                impl_num = atoi(optarg);
                break;
            case 'B':
                measure = true;
                if (optarg == NULL) {
                    print_help();
                    exit(EXIT_FAILURE);
                }
                measure_rounds = atoi(optarg);
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'd':
                decrypt = true;
                break;
            case 'h':
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        perror("Positional argument 'file' not found\n");
        print_help();
        return EXIT_FAILURE;
    }

    input_file = argv[optind];

    const char *data = read_data(input_file);
    const size_t data_length = strlen(data);

    printf("Inputted String: %s\n", data);
    printf("Length of the String: %zu\n", data_length);

    char *result;

    if (decrypt) {
        result = huffman_decode(data_length, data);
    } else {
        result = huffman_encode(data_length, data);
    }

    write_data(output_file, result);

    return EXIT_SUCCESS;
}