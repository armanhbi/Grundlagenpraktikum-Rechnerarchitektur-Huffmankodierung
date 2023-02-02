#ifndef TREE_H
#define TREE_H

#include <stdint.h>

#include "printer.h"

// Struct for one node with appropriate attributes
typedef struct Node Node;
struct Node {
    char character;
    uint16_t frequency;
    Node *left;
    Node *right;
};

/**
 * @brief Creates a tree node, given parameters
 * @param character Inserted into the node ('\0' for connecting nodes)
 * @param frequency How often does frequency occur (for connecting nodes: added children frequencies)
 * @param left, right Pointer to children nodes
 * @return Pointer to root node
 */
Node *create_node(char character, uint16_t frequency, Node *left, Node *right);

/**
 * @brief Turns tree into a dictionary
 * @param root Pointer to the root node
 * @param length_table Empty table which gets filled with the lengths of the huffman codes
 * @param lookup_table Empty table which get filled with the appropriate huffman codes
 * @param path Huffman code for the current character ("Path" in the tree)
 * @param length Length of the huffman code for the current character
 */
void tree_to_dic(Node *root, uint8_t *length_table, uint32_t *lookup_table, uint32_t path, uint8_t length);

/**
 * @brief Prints the tree (In Order)
 * @param root Pointer to the root node
 */
void print_tree_inorder(Node *root);

/**
 * @brief Frees the tree (Post Order)
 * @param root Pointer to the root node
 */
void free_node(Node *root);

#endif
