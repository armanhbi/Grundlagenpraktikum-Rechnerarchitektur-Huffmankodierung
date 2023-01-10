#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define RED "\x1b[31m"
#define WHITE "\x1B[37m"
#define CYAN "\x1B[36m"
#define GREEN "\x1B[32m"

void encode_tree_to_string(struct node *tree, char *buffer, int *cur);
struct node *decode_string_to_tree(char *compressed, int *cur);
char *huffman_encode(size_t len, const char data[len]);
char *huffman_decode(size_t len, const char data[len]);

uint8_t fast_log2(int binary);

#endif