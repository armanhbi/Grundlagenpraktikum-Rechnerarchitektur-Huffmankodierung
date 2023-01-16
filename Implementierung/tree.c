#include "tree.h"

struct node *create_node(char character, int frequency) {
    struct node *created_node = malloc(sizeof(struct node)); // save enough memory for a new node
    if (!created_node) { // check malloc
        return NULL;
    }
    created_node->character = character; // setting all attributes accordingly but no children nodes yet
    created_node->frequency = frequency;
    created_node->left = NULL;
    created_node->right = NULL;
    return created_node;
}

struct node *add_node(struct node *root, struct node *toInsert) {
    struct node *new_root = malloc(sizeof(struct node)); // save enough memory for a new node
    if (!new_root) { // check malloc
        return NULL;
    }
    new_root->character = '\0'; // empty/connecting nodes have a null byte as a character (later checked)
    new_root->frequency = root->frequency + toInsert->frequency;
    new_root->left = toInsert; // left node is the parameter and right node the original root (this node becomes the new root later on)
    new_root->right = root;
    return new_root;
}

void print_tree_inorder(struct node *root) {
    if (!root) { // recursion termination condition
        return;
    }
    print_tree_inorder(root->left); // iterate through left side
    printf("Knoten '%c': %d\n", root->character, root->frequency); // print character and its frequency
    print_tree_inorder(root->right);// iterate through right side
}

void tree_to_dic(struct node *root, uint8_t *length_table, uint16_t *lookup_table, uint16_t path, uint8_t cur_length) {
    if (!root) { // recursion termination condition
        return;
    }

    tree_to_dic(root->left, length_table, lookup_table, (path << 1), cur_length + 1); // path shifted (adding a zero), incrementing cur_length for size_table later

    if (root->character) { // if no connecting node
        length_table[root->character] = cur_length; // add the length
        lookup_table[root->character] = path;
    }

    uint16_t temp_path = (path<<1); // shifting path (adding 0) and incrementing it [see below] (turning it to a 1)
    tree_to_dic(root->right, length_table, lookup_table, ++temp_path, cur_length + 1); // incrementing cur_length
}