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

void tree_to_dic(struct node *root, uint8_t *length_table, uint16_t *lookup_table, uint16_t path, uint8_t cur_length) {
    if (!root) {
        return;
    }

    tree_to_dic(root->left, length_table, lookup_table, (path << 1), cur_length + 1);

    if (root->character) {
        length_table[root->character] = cur_length;
        lookup_table[root->character] = path;
    }

    uint16_t temp_path = path;
    temp_path<<=1;
    temp_path++;
    tree_to_dic(root->right, length_table, lookup_table, temp_path, cur_length + 1);
}