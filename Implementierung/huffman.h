#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

void encode_tree_to_string(struct node *tree, char *buffer, int *cur);
struct node *decode_tree_to_string(char *compressed, int *cur);
char* huffman_encode(size_t len, const char data[len]);
char* huffman_decode(size_t len, const char data[len]);

#endif