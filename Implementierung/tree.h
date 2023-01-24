#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

struct Node {
    char character;
    uint16_t frequency;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

// no briefs because might be changed
Node *create_node(char character, uint16_t frequency, Node *left, Node *right);
void print_tree_inorder(Node *root);
void tree_to_dic(Node *root, uint8_t *length_table, int *lookup_table, int location, uint8_t cur_length);

#endif