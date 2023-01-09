#include "tree.h"

void print_tree_inorder(struct node *root) {
    if (!root) {
        return;
    }
    print_tree_inorder(root->left);
    printf("Knoten '%c': %d\n", root->character, root->frequency);
    print_tree_inorder(root->right);
}

struct node *create_tree(char character, int frequency) {
    struct node *created_node = malloc(sizeof(struct node));
    if (!created_node) {
        return NULL;
    }
    created_node->character = character;
    created_node->frequency = frequency;
    created_node->left = NULL;
    created_node->right = NULL;
    return created_node;
}

struct node *add(struct node *root, struct node *toInsert) {
    struct node *new_root = malloc(sizeof(struct node));
    if (!new_root) {
        return NULL;
    }
    new_root->character = '\0';
    new_root->frequency = root->frequency + toInsert->frequency;
    new_root->left = toInsert;
    new_root->right = root;
    return new_root;
}