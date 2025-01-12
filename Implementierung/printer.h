#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

#define BUF_LENGTH 65535 // 2^16
#define COMPRESSED_TREE_LENGTH 2048 // enough? too much?
#define HEAP_SIZE 256 // max. size for all extended ASCII characters in heap

// Help message created with following standard: http://courses.cms.caltech.edu/cs11/material/general/usage.html
#define PRINT_HELP_MSG fprintf(stderr, "\nusage: huffman <input_file> [-V version_num] [-B rounds] [-d] [-o output_file] [-p] [-t] [-h]\n\n"\
                       "\tinput_file:\t\tPath to input file used for Huffman en-/decoding\n\n"\
                       "\t-V <version_num>:\tImplementation version to use (as number, default: 0)\n"\
                      "\t-B <rounds>:\t\tTime measurement over n rounds (as number)\n"\
                       "\t-d:\t\t\tIf set, decrypting a given Huffman code\n"\
                       "\t-o <output_file>:\tOutput file to write result to\n"\
                       "\t-p:\t\t\tPrints the algorithmic steps\n"\
                        "\t-t:\t\t\tTests the given strings/files\n"\
                        "\t-h:\t\t\tShows this help menu\n\n");

// Color Codes for nice printing
#define RED "\033[31m"
#define WHITE "\033[97m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"

extern unsigned int DEBUG_PRINT;

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
