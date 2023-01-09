#include "tree.h"

uint64_t encode_tree(struct node *tree) {
    uint64_t data = 0;
    if (tree->right == NULL && tree->left == NULL) {
        data = data<<1;
        char character = tree->character;
        data = data << character;
        return data;
    }
    data = data << encode_tree(tree->left);
    data = data << encode_tree(tree->right);
    return data;
} // possibly change to better datatype for storing binary

/**
 * @brief Turns an array of ascii characters into an savable Huffman coding
 * @param len Length of the inputted string
 * @param data Array of ascii characters
 * @return Returns a string consisting of binary code AND tree
 */
char *huffman_encode(size_t len, const char data[len]) {

    // create table (same as ascii table)
    int *table = calloc(128, sizeof(int));

    if (!table) {
        perror("Calloc did not work as expected\n");
        return "";
    }

    // increment for every letter
    for (int i = 0; i < len; i++) {
        table[(int) data[i]] += 1;
    }

    // print (for debugging)
    for (int i = 0; i < 128; i++) {
        int frequency = table[i];
        if (frequency != 0)
            printf("Der '%c' kommt %d mal vor!\n", i, table[i]);
    }

    // create tree
    struct node *root = NULL;

    // Fill table with values (search minIndex and use it and set it to 0)
    while (1) {
        int minIndex = -1;
        for (int i = 0; i < 128; i++) {
            int cur_frequency = table[i];
            if (cur_frequency != 0 && (minIndex == -1 || cur_frequency < table[minIndex])) {
                minIndex = i;
                printf("CUR: %d\n", minIndex);
            }
        }
        if (minIndex == -1) {
            break;
        }

        if (!root) {
            root = create_tree(minIndex, table[minIndex]);
        } else {
            root = add(root, create_tree(minIndex, table[minIndex]));
        }

        table[minIndex] = 0;
    }

    uint64_t test = encode_tree(root);
    printf("kommt raus: %llx\n", test);

    print_tree_inorder(root);
    free(table);
    return "";
}

/**
 * @brief Turns the Huffman code to a human readable string of ascii characters
 * @param len Length of the inputted string
 * @param data Formatted Huffman code (given as a string)
 * @return Returns a human readable string
 *
 * @details Formatted Huffman code has to include binary code AND tree (maybe even length of binary map)
 */
char *huffman_decode(size_t len, const char data[len]) {
    return "";
}