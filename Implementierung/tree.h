#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include <stdio.h>

struct node {
    char character;
    int frequency;
    struct node *left;
    struct node *right;
};

struct node *create_tree(char character, int frequency);
struct node *add(struct node *root, struct node *toInsert);
void print_tree_inorder(struct node *root);

#endif