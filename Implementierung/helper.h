#ifndef IMPLEMENTIERUNG_HELPER_H
#define IMPLEMENTIERUNG_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
#define BUF_LENGTH 65535
#define COMPRESSED_TREE_LENGTH 1024

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

void file_error(FILE *fd, char *msg);
uint8_t createMask(int number);
void print_binary(char integer, uint8_t length);

#endif
