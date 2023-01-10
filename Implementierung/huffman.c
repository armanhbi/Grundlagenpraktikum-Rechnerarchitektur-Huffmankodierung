#include "tree.h"
#include <string.h>

void encode_tree_to_string(struct node *tree, char *buffer, int *cur) {
    if (tree->right == NULL && tree->left == NULL) {
        char character = tree->character;
        buffer[(*cur)++] = '1';
        for (int i = 9; i > 1; i--) {
            char c = (character&0x80)>>7 ? '1' : '0'; // Bit hack to get the first bit of the character
            buffer[(*cur)++] = c;
            character<<=1;
        }
        return;
    }
    buffer[(*cur)++] = '0';
    encode_tree_to_string(tree->left, buffer, cur);
    encode_tree_to_string(tree->right, buffer, cur);
}

struct node *decode_tree_to_string(char *compressed, int *cur) {
    struct node *cur_node = create_tree('\0', 0);
    cur_node->left = NULL;
    cur_node->right = NULL;

    while (compressed[*cur] != '\0') {
        if (compressed[*cur] == 49) { // ascii for '1'
            char character;
            for (int i = 1; i < 9; i++) {
                character<<=1;
                if (compressed[(*cur)+i]-49 == 0) {
                    character++;
                }
            }
            cur_node->character = character;
            (*cur)+=8;
            return cur_node;
        }
        ++(*cur);
        cur_node->left = decode_tree_to_string(compressed, cur);
        ++(*cur);
        cur_node->right = decode_tree_to_string(compressed, cur);
        (*cur)++;
    }
    return cur_node;
}

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

    print_tree_inorder(root);

    char *buffer = malloc(512); // malloc check
    int *cur = malloc(1); // malloc check
    encode_tree_to_string(root, buffer, cur);
    printf("Compressed tree ready to be saved: %s\n", buffer);

    int *cur2 = malloc(1); // malloc check
    struct node *root2 = decode_tree_to_string(buffer, cur2);

    print_tree_inorder(root2);

    free(table);
    free(buffer);
    free(cur);
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