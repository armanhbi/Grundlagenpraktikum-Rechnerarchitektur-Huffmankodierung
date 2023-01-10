#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

struct node {
    char character;
    int frequency;
    struct node *left;
    struct node *right;
};

struct node *create_node(char character, int frequency);
struct node *add_node(struct node *root, struct node *toInsert);
void print_tree_inorder(struct node *root);
void tree_to_dic(struct node *root, uint64_t *used_table, char *lookup_table, uint8_t location);

#endif