#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>

#include "huffman.h"
#include "input_output.h"
#include "helper.h"

int main(int argc, char **argv) {
    // Checking if program and arguments are valid
    if (argc < 2) {
        PRINT_HELP_MSG
        return 0;
        //return EXIT_FAILURE;
    }

    int impl_num = 0;
    bool measure = false;
    int measure_rounds = 0;
    char *input_file;
    bool decrypt = false;
    char *output_file = "\0";

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
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
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
                PRINT_HELP_MSG
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        perror("Positional argument 'file' not found\n");
        PRINT_HELP_MSG
        return EXIT_FAILURE;
    }

    input_file = argv[optind];

    char *data;
    if (decrypt) {
        data = read_binary(input_file);
    } else {
        data = read_data(input_file);
    }
    size_t data_length = strlen(data);

    // print (for debugging)
    printf("\n%sBasic Information%s", CYAN, WHITE);
    printf("\nString in file: '%s%s%s' (Length: %s%zu%s)\n\n", RED, data, WHITE, RED, data_length, WHITE);

    if (decrypt) {
        data = huffman_decode(data_length, data);
    } else {
        data = huffman_encode(data_length, data);
    }

    printf("\nRETURN VALUE: %s%s%s\n", RED, data, WHITE);
    printf("\n");

    int *cur2 = malloc(1); // malloc check
    struct node *root2 = decode_string_to_tree(data, cur2);

    // print (for debugging)
    printf("%sRebuild tree (debug)%s\n", CYAN, WHITE);
    print_tree_inorder(root2);

    if (strlen(output_file) && strlen(data)) {
        if (decrypt) {
            write_data(output_file, data);
        } else {
            write_binary(output_file, data);
        }
    }

    return EXIT_SUCCESS;
}