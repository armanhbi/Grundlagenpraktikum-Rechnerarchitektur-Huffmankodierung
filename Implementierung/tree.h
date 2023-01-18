#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

struct Node {
    char character;
    int frequency;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

// no briefs because might be changed
Node *create_node(char character, int frequency);
Node *add_node(Node *root, Node *toInsert);
void print_tree_inorder(Node *root);
void tree_to_dic(Node *root, uint8_t *length_table, uint16_t *lookup_table, uint16_t location, uint8_t cur_length);

#endif