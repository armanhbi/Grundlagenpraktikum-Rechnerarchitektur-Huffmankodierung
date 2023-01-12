#include "huffman.h"

void encode_tree_to_string(struct node *tree, char *buffer, int *cur) {
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
    encode_tree_to_string(tree->left, buffer, cur);
    encode_tree_to_string(tree->right, buffer, cur);
}

struct node *decode_string_to_tree(char *compressed, int *cur) {
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
        cur_node->left = decode_string_to_tree(compressed, cur);
        ++(*cur);
        cur_node->right = decode_string_to_tree(compressed, cur);
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
    uint64_t *used_table = malloc(2 * sizeof(uint64_t));
    char *lookup_table = malloc(128 * sizeof(char)); // malloc check
    int *cur = malloc(sizeof(int));
    tree_to_dic(root, used_table, lookup_table, 0);
    print_binary_array(used_table, 128);

    // print (for debugging)
    printf("%sDictionary%s\n", CYAN, WHITE);
    uint64_t mask = 0x8000000000000000;
    for (int i = 0; i < 128; i++) {
        if (!mask)
            mask = 0x8000000000000000;
        int index = (int) (double) i / 64.0;
        if (used_table[index] & mask) {
            printf("'%c' -> ", i);
            print_binary(lookup_table[i]);
            printf("\n");
        }
        mask>>=1;
    }
    printf("\n");

    uint64_t huffman[128 * sizeof(uint64_t)] = {0}; // nicht mehr als 8192 bytes möglich

    int huffman_index = 0;
    uint8_t available_space_block = 64;
    for (int i = 0; i < len; i++) {
        uint8_t code = lookup_table[data[i]];
        uint8_t to_log = fast_log2(code); // wieviel platz brauchen die bits

        if (available_space_block >= to_log) { // wenn im block genug platz verfügbar ist

            huffman[huffman_index] <<= to_log; // shift
            huffman[huffman_index] |= code; // combine (with logical OR)
            available_space_block -= to_log;

        } else {

            huffman[huffman_index] <<= available_space_block; // soviel wie vorhanden shiften
            to_log -= available_space_block;
            huffman[huffman_index] |= ((code & (createMask(available_space_block)
                    << to_log)) >> to_log); // die ersten available_space_block stellen

            huffman_index += 1;

            huffman[huffman_index] |= (code & createMask(to_log)); // die letzten to_log stellen
            available_space_block = 64 - to_log;

        }
    }
    huffman[huffman_index] <<= available_space_block;
    int huffman_length = huffman_index * 64 + (64 - available_space_block);

    printf("%sEncode tree%s (Huffman Length: %s%d%s)\n", CYAN, WHITE, RED, huffman_length, WHITE); // print (for debugging)
    print_binary_array(huffman, huffman_length);
    printf("%s\n", WHITE);

    char *buffer = malloc(512 * sizeof(char)); // malloc check
    *cur = 0; // malloc check
    printf("%sCompressed tree%s\n", CYAN, WHITE); // print (for debugging)
    encode_tree_to_string(root, buffer, cur);

    free(cur);
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