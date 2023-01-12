#include "tree.h"

struct node *create_node(char character, int frequency) {
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

struct node *add_node(struct node *root, struct node *toInsert) {
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

void print_tree_inorder(struct node *root) {
    if (!root) {
        return;
    }
    print_tree_inorder(root->left);
    printf("Knoten '%c': %d\n", root->character, root->frequency);
    print_tree_inorder(root->right);
}

void tree_to_dic(struct node *root, uint64_t *used_table, char *lookup_table, uint8_t location) {
    if (!root) {
        return;
    }
    tree_to_dic(root->left, used_table, lookup_table, (location << 1));
    if (root->character) {
        uint64_t mask = (uint64_t) 1 << (63 - (root->character % 64));
        int index = (int) ((double) root->character / 64.0);
        used_table[index] |= mask;
        lookup_table[root->character] = location;
    }
    uint8_t temp_loc = location;
    temp_loc<<=1;
    temp_loc++;
    tree_to_dic(root->right, used_table, lookup_table, temp_loc);
}