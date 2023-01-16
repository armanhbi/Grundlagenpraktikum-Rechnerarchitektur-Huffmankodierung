#include "huffman.h"

int encode_tree(struct node *tree, char *buffer, int *index) {
    if (tree->right == NULL && tree->left == NULL) {
        char character = tree->character;
        buffer[(*index)++] = '1';
        printf("1 ");
        printf("%c (", character);
        for (int i = 9; i > 1; i--) {
            char c = (character & 0x80) >> 7 ? '1' : '0'; // bithack to get the first bit of the character
            buffer[(*index)++] = c;
            character <<= 1;
            putchar(c);
        }
        printf(") ");
        return 0; // egal
    }
    buffer[(*index)++] = '0';
    printf("0 ");
    encode_tree(tree->left, buffer, index);
    encode_tree(tree->right, buffer, index);
    return *index;
}

struct node *decode_tree(char *compressed, int *index) {
    struct node *cur_node = create_node('\0', 0);
    cur_node->left = NULL;
    cur_node->right = NULL;

    while (compressed[*index] != '\n' && *index < 100) {
        if (compressed[*index] == 49) { // ascii for '1'
            char character = '\0';
            for (int i = 1; i < 9; i++) {
                character <<= 1;
                if (compressed[(*index) + i] - 49 == 0) {
                    character++;
                }
            }
            cur_node->character = character;
            (*index) += 9;
            return cur_node;
        }
        ++(*index);
        cur_node->left = decode_tree(compressed, index);
        cur_node->right = decode_tree(compressed, index);
    }
    return cur_node;
}

char *huffman_encode(size_t len, const char data[len]) {
    int table[128] = {0}; // create table (same as ascii table)

    for (size_t i = 0; i < len; i++) {
        table[(int) data[i]] += 1; // increment for every letter (counting appearance)
    }

    // print (for debugging)
    printf("%sHäufigkeitsanalyse%s\n", CYAN, WHITE);
    for (int i = 0; i < 128; i++) {
        int frequency = table[i];
        if (frequency != 0)
            printf("Der '%c' kommt %s%d%s mal vor!\n", i, RED, table[i], WHITE);
    }
    printf("\n");

    struct node *root = NULL; // create tree

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
    printf("\n\n");

    // Huffman Array with comrpessedtree + \n + huffmancode
    char *huffman = malloc(BUF_LENGTH * sizeof(char)); // malloc check

    // Compress tree
    int index[1] = {0};
    printf("%sCompressed tree%s\n", CYAN, WHITE); // print (for debugging)
    int huffman_index = encode_tree(root, huffman, index);

    huffman[huffman_index++] = '\n';

    // turn tree to dictionary
    uint8_t length_table[128] = {0};
    uint16_t lookup_table[128] = {0};

    tree_to_dic(root, length_table, lookup_table, 0, 0);

    // print (for debugging)
    printf("%sDictionary%s\n", CYAN, WHITE);
    for (int i = 0; i < 128; i++) {
        if (length_table[i] != 0) {
            printf("'%c' -> ", i);
            print_binary(lookup_table[i], length_table[i]);
            printf(" (Länge: %d)", length_table[i]);
            printf("\n");
        }
    }
    printf("\n");

    for (size_t i = 0; i < len; i++) {
        uint16_t code = lookup_table[(uint16_t) data[i]];
        uint8_t length = length_table[(uint8_t) data[i]];
        uint16_t mask = 1 << (length - 1);

        for (int i = 0; mask; i++) {
            huffman[huffman_index++] = ((code & mask) >> (length - 1 - i)) ? '1' : '0';
            mask >>= 1;
        }
    }

    return huffman;
}

char *huffman_decode(size_t len, const char data[len]) {
    char *buf = malloc(BUF_LENGTH); // save enough space for up to BUF_LENGTH characters
    uint32_t index = 0;
    size_t seperator = 0;

    if(!buf){
        perror("Error: Buffer could not be allocated");
        return NULL;
    }

    //find seperator in data of tree and decoding string
    for(int i = 0; i < len; i++){ //
        if(data[i] == '\n'){
            seperator = i;
            break;
        }
    }

    //nothing to decode or no new line in data
    if(seperator == 0){
        return buf;
    }

    //makes tree from data
    int cur[1] = {0};
    struct node *tree_root = decode_tree(&data[0], cur);


    //
    for(int i = seperator + 1; i< len;i++){
        struct node *pointer = tree_root;

        /*if(pointer->left == NULL && pointer->right == NULL) {
            buf[index] = pointer->character;
            break; // stimmt das?
        }*/

        if (data[i] == '0') {

        } else if (data[i] == '1') {

        }
    }

    return "";
}