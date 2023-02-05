#include "tree.h"

Node *create_node(char character, uint16_t frequency, Node *left, Node *right) {
    Node *created_node = calloc(1, sizeof(Node)); // save enough memory for a new node
    if (!created_node) { // check calloc
        perror("TreeException: Memory for a node could not be allocated");
        return NULL;
    }
    created_node->character = character; // setting all attributes accordingly
    created_node->frequency = frequency;
    created_node->left = left;
    created_node->right = right;
    return created_node;
}

void print_tree_inorder(Node *root) {
    if (!root) { // recursion termination condition and general null check
        return;
    }
    print_tree_inorder(root->left); // iterate through left side
    print("Knoten '%c': %d\t", root->character, root->frequency); // print character and its frequency
    print_tree_inorder(root->right); // iterate through right side
}

void tree_to_dic(Node *root, uint8_t *length_table, uint32_t *lookup_table, uint32_t path, uint8_t length) {
    if (!root || !length_table || !lookup_table) { // recursion termination condition and null check
        return;
    }

    // path shifted left (adding a zero), incrementing length for size_table later
    tree_to_dic(root->left, length_table, lookup_table, path << 1, length + 1);

    if (root->character) { // if no connecting node
        length_table[(uint8_t) root->character] = length; // add the length
        lookup_table[(uint8_t) root->character] = path; // add tree path to certain character
    }

    // shifting path (adding 0) and incrementing it (with logical OR operation -> turning it to a 1)
    tree_to_dic(root->right, length_table, lookup_table, path << 1 | 1, length + 1); // incrementing length
}

void free_node(Node *root) {
    if (!root) { // recursion termination condition and general null check
        return;
    }
    free_node(root->left); // iterate through left side
    free_node(root->right); // iterate through right side
    if (root) // If root exists, free it
        free(root);
}
