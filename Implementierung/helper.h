#ifndef IMPLEMENTIERUNG_HELPER_H
#define IMPLEMENTIERUNG_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_LENGTH 131072
#define COMPRESSED_TREE_LENGTH 2048

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
#define PRINT_HELP_MSG perror("\nusage: huffman <input_file> [-V version_num] [-B n] [-d] [-o output_file] [-h]\n\n"\
                       "\tinput_file:\t\tPath to input file used for Huffman en-/decoding\n\n"\
                       "\t-V <version_num>:\tImplementation version to use (as number, default: 0)\n"\
                       "\t-B <n>:\t\t\tTime measurement over n rounds (as number)\n"\
                       "\t-d:\t\t\tIf set, decrypting a given Huffman code\n"\
                       "\t-o <output_file>:\tOutput file to write result to\n"\
                       "\t-h:\t\t\tShows this help menu\n\n");

#define RED "\033[31m"
#define WHITE "\033[97m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"

/**
 * @brief Prints error message, closes file descriptor (if still open) and exits (with failure)
 * @param fd File descriptor (pointer to file)
 * @param msg String of error message
 */
void file_error(FILE *fd, char *msg);

/**
 * @brief Prints a character as binary (with set length)
 * @param integer ASCII Character encoded as integer
 * @param length Length of binary code
 */
void print_binary(char integer, uint8_t length);

#endif
