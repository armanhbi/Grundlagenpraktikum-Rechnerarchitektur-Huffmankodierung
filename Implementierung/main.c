#include <stdbool.h>
#include <getopt.h>
#include <string.h>

#include "huffman.h"
#include "input_output.h"

int main(int argc, char **argv) {
    // Checking if program and arguments are valid
    if (argc < 2) {
        PRINT_HELP_MSG
        return EXIT_FAILURE;
    }

    int impl_num = 0;
    bool measure = false; // Measure performance
    int measure_rounds = 0; // How often?
    char *input_file; // Path
    bool decrypt = false;
    char *output_file;

    // --help for -h
    static struct option help_synonym[] = {
            {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "V:B:o:dh", help_synonym, NULL)) != -1) {
        switch (opt) {
            case 'V':
                impl_num = atoi(optarg); // Interpret the argument as number (atoi)
                break;
            case 'B':
                measure = true; // if measurement flag is set
                if (optarg == NULL) {
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
                }
                measure_rounds = atoi(optarg); // How often should performance be measured
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'd':
                decrypt = true;
                break;
            case 'h': // Fallthrough
            default:
                PRINT_HELP_MSG
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) { // If there is no input file (necessary!)
        perror("Positional argument 'file' not found\n");
        PRINT_HELP_MSG
        return EXIT_FAILURE;
    }

    input_file = argv[optind];

    // STARTING HUFFMAN EN-/DECODING

    char *data;
    data = read_data(input_file); // Read string out of input file
    size_t data_length = strlen(data); // Measure length

    // Print basic details and information about flags
    print("\n%sBasic Information%s", CYAN, WHITE);
    print("\nInput File: %s", input_file);
    print("\nVersion: %d", impl_num);
    print("\nTesting: %s (with %d rounds)", measure ? "true" : "false", measure_rounds);
    print("\nDecrypt: %s", decrypt ? "true" : "false");
    print("\nOutput File: %s\n", output_file);

    print("\nString in file: '%s%s%s' (Length: %s%zu%s)\n\n", RED, data, WHITE, RED, data_length, WHITE);

    if (decrypt) {
        data = huffman_decode(data_length, data);
    } else {
        data = huffman_encode(data_length, data);
    }

    if (!data)
        return EXIT_FAILURE;

    print("%sRETURN VALUE%s\n", CYAN, WHITE);
    print("'%s%s%s'\n", RED, data, WHITE);

    // If output file was set / Data has value write data (HM code / decoded code) to output file
    if (strlen(output_file) && strlen(data)) {
        write_data(output_file, data);
    }

    free(data);
    return EXIT_SUCCESS;
}