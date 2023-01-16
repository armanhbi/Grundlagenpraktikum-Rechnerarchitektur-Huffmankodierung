#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

struct node {
    char character;
    int frequency;
    struct node *left;
    struct node *right;
};

struct node *create_node(char character, int frequency);
struct node *add_node(struct node *root, struct node *toInsert);
void print_tree_inorder(struct node *root);
void tree_to_dic(struct node *root, uint8_t *length_table, uint16_t *lookup_table, uint16_t location, uint8_t cur_length);

#endif