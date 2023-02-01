#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "printer.h"

/**
 * @brief Reads the data from path into buf
 * @param path Path to the file
 * @return Returns the string saved in the file (Huffman encoding or normal ascii characters)
 */
char *read_data(char *path);

/**
 * @brief Saves the string in result into path
 * @param path Where the result should be saved
 * @param result Either Huffman encoding or normal ascii string
 */
void write_data(char *path, char *result);

#endif