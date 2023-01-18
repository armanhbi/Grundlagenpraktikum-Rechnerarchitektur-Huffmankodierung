#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "tree.h"
#include "input_output.h"

/**
 * @brief Compresses the tree data structure into an bit code (Inspiration: https://stackoverflow.com/questions/759707/efficient-way-of-storing-huffman-tree)
 * @param tree Pointer to the root of the binary tree data structure
 * @param buffer At the end: contains bit code
 * @param index Pointer to an integer pointing to the next free space in buffer (needed for recursion purposes only) (fuck C-language)
 * @return Length of the bit code
 */
int encode_tree(Node *tree, char *buffer, int *index);

/**
 * @brief Decodes the compressed tree (as a string) back to a binary tree
 * @param compressed Pointer to the root of the tree data structure
 * @param index Pointer to an integer pointing to the next character in the buffer (recursion)
 * @return Pointer to root of the binary tree (decompressed)
 */
Node *decode_tree(const char *compressed, int *index);

/**
 * @brief Turns an array of ascii characters into an savable Huffman coding
 * @param len Length of the inputted string
 * @param data Array of ascii characters
 * @return Returns a string consisting of binary code AND tree
 */
char *huffman_encode(size_t len, const char data[len]);

/**
 * @brief Turns the Huffman code to a human readable string of ascii characters
 * @param len Length of the inputted string
 * @param data Formatted Huffman code (given as a string)
 * @return Returns a human readable string
 *
 * @details Formatted Huffman code has to include binary code AND tree (maybe even length of binary map)
 */
char *huffman_decode(size_t len, const char data[len]);

#endif