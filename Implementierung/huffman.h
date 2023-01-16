#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "tree.h"
#include "input_output.h"

void encode_tree(struct node *tree, char *buffer, int *index);
struct node *decode_tree(char *compressed, int *index);
char *huffman_encode(size_t len, const char data[len]);
char *huffman_decode(size_t len, const char data[len]);

uint8_t fast_log2(int binary);

#endif