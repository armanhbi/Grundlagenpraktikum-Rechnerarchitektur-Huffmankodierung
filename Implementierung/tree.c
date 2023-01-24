#include "tree.h"

Node *create_node(char character, uint16_t frequency, Node *left, Node *right) {
    Node *created_node = malloc(sizeof(Node)); // save enough memory for a new node
    if (!created_node) { // check malloc
        return NULL;
    }
    created_node->character = character; // setting all attributes accordingly but no children nodes yet
    created_node->frequency = frequency;
    created_node->left = left;
    created_node->right = right;
    return created_node;
}

void print_tree_inorder(Node *root) {
    if (!root) { // recursion termination condition
        return;
    }
    print_tree_inorder(root->left); // iterate through left side
    printf("Knoten '%c': %d\t", root->character, root->frequency); // print character and its frequency
    print_tree_inorder(root->right);// iterate through right side
}

void tree_to_dic(Node *root, uint8_t *length_table, int *lookup_table, int path, uint8_t cur_length) {
    if (!root) { // recursion termination condition
        return;
    }

    tree_to_dic(root->left, length_table, lookup_table, (path << 1), cur_length + 1); // path shifted (adding a zero), incrementing cur_length for size_table later

    if (root->character) { // if no connecting node
        length_table[(uint8_t) root->character] = cur_length; // add the length
        lookup_table[(uint16_t) root->character] = path;
    }

    uint16_t temp_path = (path<<1); // shifting path (adding 0) and incrementing it [see below] (turning it to a 1)
    tree_to_dic(root->right, length_table, lookup_table, ++temp_path, cur_length + 1); // incrementing cur_length
}