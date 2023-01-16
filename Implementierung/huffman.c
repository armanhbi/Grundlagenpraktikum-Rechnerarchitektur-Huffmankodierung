#include "huffman.h"

void encode_tree(struct node *tree, char *buffer, int *cur) {
    if (tree->right == NULL && tree->left == NULL) {
        char character = tree->character;
        buffer[(*cur)++] = '1';
        printf("1 ");
        printf("%c (", character);
        for (int i = 9; i > 1; i--) {
            char c = (character & 0x80) >> 7 ? '1' : '0'; // Bit hack to get the first bit of the character
            buffer[(*cur)++] = c;
            character <<= 1;
            putchar(c);
        }
        printf(") ");
        return;
    }
    buffer[(*cur)++] = '0';
    printf("0 ");
    encode_tree(tree->left, buffer, cur);
    encode_tree(tree->right, buffer, cur);
}

struct node *decode_tree(char *compressed, int *cur) {
    struct node *cur_node = create_node('\0', 0);
    cur_node->left = NULL;
    cur_node->right = NULL;

    while (compressed[*cur] != '\0') {
        if (compressed[*cur] == 49) { // ascii for '1'
            char character;
            for (int i = 1; i < 9; i++) {
                character <<= 1;
                if (compressed[(*cur) + i] - 49 == 0) {
                    character++;
                }
            }
            cur_node->character = character;
            (*cur) += 8;
            return cur_node;
        }
        ++(*cur);
        cur_node->left = decode_tree(compressed, cur);
        ++(*cur);
        cur_node->right = decode_tree(compressed, cur);
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
    int table[128] = {0};

    // increment for every letter
    for (int i = 0; i < len; i++) {
        table[(int) data[i]] += 1;
    }

    // print (for debugging)
    printf("%sHäufigkeitsanalyse%s\n", CYAN, WHITE);
    for (int i = 0; i < 128; i++) {
        int frequency = table[i];
        if (frequency != 0)
            printf("Der '%c' kommt %s%d%s mal vor!\n", i, RED, table[i], WHITE);
    }
    printf("\n");

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
            root = create_node(minIndex, table[minIndex]);
        } else {
            root = add_node(root, create_node(minIndex, table[minIndex]));
        }

        table[minIndex] = 0;
    }

    // print (for debugging)
    printf("%sTree creation%s\n", CYAN, WHITE);
    print_tree_inorder(root);
    printf("\n");

    // turn tree to dictionary
    uint8_t length_table[128] = {0};
    uint16_t lookup_table[128] = {0};

    int cur[1] = {0};
    tree_to_dic(root, length_table, lookup_table, 0, 0);

    // print (for debugging)
    printf("%sDictionary%s\n", CYAN, WHITE);
    for (int i = 0; i < 128; i++) {
        if (length_table[i] != 0) {
            printf("'%c' -> ", i);
            print_binary(lookup_table[i]);
            printf(" (Länge: %d)", length_table[i]);
            printf("\n");
        }
    }
    printf("\n");

    char *huffman = malloc(65536 * sizeof(char));

    int huffman_index = 0;
    for (int i = 0; i < len; i++) {
        uint16_t code = lookup_table[data[i]];
        uint16_t mask = 0x8000;

        while (code) {
            huffman[huffman_index++] = (code & mask) ? '1' : '0';
            code<<=1;
        }
    }

    printf("%sEncode tree%s (Huffman Length: %s%d%s)%s\n", CYAN, WHITE, RED, huffman_index, WHITE, RED); // print (for debugging)
    for (int i = 0; i < huffman_index; i++) {
        printf("%c", huffman[i]);
    }
    printf("%s\n", WHITE);

    char *buffer = malloc(512 * sizeof(char)); // malloc check
    *cur = 0;
    printf("%sCompressed tree%s\n", CYAN, WHITE); // print (for debugging)
    encode_tree(root, buffer, cur);

    return buffer;
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