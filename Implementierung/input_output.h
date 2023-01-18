#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "helper.h"

/**
 * @brief Reads the data from path into buf
 * @param path Path to the file
 * @return Returns the string saved in the file (Huffman encoding or normal ascii characters)
 */
char *read_data(char *path);

/**
 * @brief Saves the string in result into path
 * @param path where the result should be saved
 * @param result either Huffman encoding or normal ascii string
 */
void write_data(char *path, char *result);

#endif