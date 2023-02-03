#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#define BUF_LENGTH 262144 // 2^18
#define COMPRESSED_TREE_LENGTH 2048 // enough? too much?
#define DEBUG_PRINT 0

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
#define PRINT_HELP_MSG fprintf(stderr, "\nusage: huffman <input_file> [-V version_num] [-B n] [-d] [-o output_file] [-h]\n\n"\
                       "\tinput_file:\t\tPath to input file used for Huffman en-/decoding\n\n"\
                       "\t-V <version_num>:\tImplementation version to use (as number, default: 0)\n"\
                      "\t-B <n>:\t\t\tTime measurement over n rounds (as number)\n"\
                       "\t-d:\t\t\tIf set, decrypting a given Huffman code\n"\
                       "\t-o <output_file>:\tOutput file to write result to\n"\
                       "\t-h:\t\t\tShows this help menu\n\n");

// Color Codes for nice printing
#define RED "\033[31m"
#define WHITE "\033[97m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"

/**
 * @brief Prints a character as binary (with set length)
 * @param integer ASCII Character encoded as integer
 * @param length Length of binary code
 */
void print_binary(char integer, uint8_t length);

/**
 * @brief Print if flag set
 * @param msg, c Char (array) as message
 */
void print(const char *format, ...);
void put_chr(const char c);

#endif
