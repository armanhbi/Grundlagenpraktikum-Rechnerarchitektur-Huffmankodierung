#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "huffman.h"
#include "input_output.h"
#include "printer.h"
#include "testing.h"
#include "shannonfano.h"

int main(int argc, char **argv) {
    // Checking if program and arguments are valid
    if (argc < 2) {
        PRINT_HELP_MSG
        return EXIT_FAILURE;
    }

    int impl_num = 0;
    bool measure = false; // Measure performance
    unsigned int measure_rounds = 1; // How often?
    char *input_file = NULL; // Path
    bool decrypt = false;
    char *output_file = NULL;

    // --help for -h
    static struct option help_synonym[] = {
            {.name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h'}
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "V:B:o:dhtp", help_synonym, NULL)) != -1) {
        switch (opt) {
            case 'V':
                if (optarg == NULL) {
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
                }
                impl_num = atoi(optarg); // Interpret the argument as number (atoi) -> on error returns 0
                break;
            case 'B':
                measure = true; // if measurement flag is set
                if (optarg == NULL) {
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
                }
                measure_rounds = atoi(optarg); // How often should performance be measured
                if (measure_rounds == 0 || measure_rounds == 1) {
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
                if (optarg == NULL) {
                    PRINT_HELP_MSG
                    return EXIT_FAILURE;
                }
                output_file = optarg;
                break;
            case 'p':
                DEBUG_PRINT = 1;
                break;
            case 'd':
                decrypt = true;
                break;
            case 't':
                test_all();
                return EXIT_SUCCESS;
            case 'h': // Fallthrough
            default:
                PRINT_HELP_MSG
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) { // If there is no input file (necessary arg!)
        perror("Positional argument 'file' not found");
        PRINT_HELP_MSG
        return EXIT_FAILURE;
    }

    input_file = argv[optind];

    struct timespec start_time;
    struct timespec end_time;
    double added_times = 0.0;

    // STARTING HUFFMAN EN-/DECODING

    for (size_t i = 0; i < measure_rounds; i++) {
        char *data = NULL;
        uint32_t data_length[1] = {0}; // Measure length
        data = read_data(input_file, data_length); // Read string out of input file

        if (measure)
            clock_gettime(CLOCK_MONOTONIC, &start_time);

        if (data == NULL) {
            PRINT_HELP_MSG
            return EXIT_FAILURE;
        }

        if (*data_length == 0) {
            perror("String is empty");
            PRINT_HELP_MSG
            return EXIT_FAILURE;
        }

        // Print basic details and information about flags
        print("\n%sBasic Information%s", CYAN, WHITE);
        print("\nInput File: %s", input_file);
        print("\nVersion: %d", impl_num);
        print("\nMeasurement: %s (with %d rounds)", measure ? "true" : "false", measure_rounds);
        print("\nDecrypt: %s", decrypt ? "true" : "false");
        print("\nOutput File: %s\n", output_file);

        print("\nString in file: '%s%s%s' (Length: %s%zu%s)\n\n", RED, data, WHITE, RED, *data_length, WHITE);

        char *result = NULL;

        switch (impl_num) {
            case 1:
                if (decrypt) {
                    //result = huffman_decode(*data_length, data);
                } else {
                    result = shannonfano_encode(*data_length, data);
                }
                break;
            default:
                if (decrypt) {
                    result = huffman_decode(*data_length, data);
                } else {
                    result = huffman_encode(*data_length, data);
                }
                break;
        }

        if (result == NULL)
            return EXIT_FAILURE;

        if (measure)
            clock_gettime(CLOCK_MONOTONIC, &end_time);

        if (!decrypt) {
            uint64_t without = *data_length * 8;
            uint32_t with = strlen(result);
            print("%sOhne Codierung:\t\t %d Bits%s\n", CYAN, without, WHITE);
            print("%sMit Codierung:\t\t %d Bits%s\n", CYAN, with, WHITE);
            double rate = (double) with / without;
            print("%sHuffman Rate:\t\t %f%s\n\n", CYAN, rate, WHITE);
        }

        print("%sRETURN VALUE%s\n", CYAN, WHITE);
        print("'%s%s%s'\n", RED, result, WHITE);

        // If output file was set / Data has value write data (HM code / decoded code) to output file
        if (output_file) {
            if (write_data(output_file, result)) {
                free(result);
                free(data);
                return EXIT_FAILURE;
            }
        }

        free(result);
        free(data);

        if (measure) {
            double time = end_time.tv_sec - start_time.tv_sec + 1e-9 * (end_time.tv_nsec - start_time.tv_nsec);
            added_times += time;
            printf("\nIteration %zu -> verbrauchte Zeit: %f\n", i, time);
        }
    }

    if (measure)
        printf("\nDurchschnittlich verbrauchte Zeit: %f\n", (added_times/measure_rounds));

    return EXIT_SUCCESS;
}
