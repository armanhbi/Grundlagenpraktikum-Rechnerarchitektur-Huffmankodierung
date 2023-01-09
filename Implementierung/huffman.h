#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

void print_error(char *msg);
char* huffman_encode(size_t len, const char data[len]);
char* huffman_decode(size_t len, const char data[len]);
uint64_t encode_tree(struct node *tree);

#endif