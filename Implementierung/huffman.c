#include "huffman.h"

int encode_tree(Node *tree, char *buffer, int *index) {
    if (tree->right == NULL && tree->left == NULL) { // node with valid character was reached
        char character = tree->character;
        buffer[(*index)++] = '1'; // '1' meaning an 8 bit character will follow
        printf("1 ");
        printf("%c (", character);
        for (int i = 9; i > 1; i--) {
            char c = (character & 0x80) >> 7 ? '1' : '0'; // bithack to get the first bit of the character
            buffer[(*index)++] = c; // write character bit for bit into the buffer
            character <<= 1;
            putchar(c);
        }
        printf(") ");
        return 0; // irrelevant
    }
    buffer[(*index)++] = '0';
    printf("0 ");
    encode_tree(tree->left, buffer, index); // adding a '0' everytime it moves further down and do recursion
    encode_tree(tree->right, buffer, index);
    return *index; // return length of the buffer
}

Node *decode_tree(const char *compressed, int *index) {
    Node *cur_node = create_node('\0', 0, NULL, NULL); // Create the upper node (always \0)
    cur_node->left = NULL;
    cur_node->right = NULL;

    if (compressed[*index] != '\n') { // iterate through the buffer
        if (compressed[*index] == 49) { // ascii for '1' (8 bit character follows)
            char character = '\0';
            for (int i = 1; i < 9; i++) {
                character <<= 1; // shifting character and adding 1 if bit was set -> character is loaded from binary ascii code
                if (compressed[(*index) + i] - 49 == 0) {
                    character++;
                }
            }
            cur_node->character = character;
            (*index) += 9; // add 9 ('1' + 8 bit character)
            return cur_node;
        }
        ++(*index);
        cur_node->left = decode_tree(compressed, index); // recursion for left first than right side
        cur_node->right = decode_tree(compressed, index);
        print_tree_inorder(cur_node);
    }
    return cur_node; // return upper root node/tree
}

char *huffman_encode(size_t len, const char data[len]) {
    Node* table[HEAP_SIZE] = {0}; // create table (same as unicode table (8 bits))

    for (size_t i = 0; i < len; i++) {
        if (table[(uint8_t) data[i]] == NULL) {
            table[(uint8_t) data[i]] = create_node(data[i], 1, NULL, NULL);
        } else {
            table[(uint8_t) data[i]]->frequency += 1; // increment for every letter (counting appearance)
        }
    }

    Heap *heap = create_heap(HEAP_SIZE); //Min Heap

    // print (for debugging)
    printf("%sHäufigkeitsanalyse%s\n", CYAN, WHITE);
    for (uint16_t i = 0; i < 256; i++) {

        if (table[i] == 0x0) // if pointer is null
            continue;

        uint16_t frequency = table[i]->frequency;
        if (frequency != 0) {
            printf("Der '%c' kommt %s%d%s mal vor!\n", i, RED, frequency, WHITE);
            insert(heap, table[i]);
        }
    }
    printf("\n");

    while(heap->count > 1) { // kombiniere außer es gibt keine 2 nodes
        Node *min1 = pop_min(heap);
        Node *min2 = pop_min(heap);

        Node *connector = create_node('\0', min1->frequency + min2->frequency, min1, min2);

        insert(heap, connector);
    }

    Node *root = pop_min(heap);

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
    uint8_t length_table[128] = {0}; // savable in 3 bits -> max. length of 8
    int lookup_table[128] = {0};

    tree_to_dic(root, length_table, lookup_table, 0, 0);

    // print (for debugging)
    printf("\n\n%sDictionary%s\n", CYAN, WHITE);
    for (uint8_t i = 0; i < 128; i++) {
        if (length_table[i] != 0) {
            printf("'%c' -> ", i);
            print_binary(lookup_table[i], length_table[i]);
            printf(" (Länge: %d)", length_table[i]);
            printf("\n");
        }
    }
    printf("\n");

    // code (and length of it) of every letter
    for (size_t i = 0; i < len; i++) {
        int code = lookup_table[(uint16_t) data[i]];
        uint8_t length = length_table[(uint8_t) data[i]];
        int mask = 1 << (length - 1); // mask moving from length to the end of the character (right side)

        for (int i = 0; mask; i++) {
            huffman[huffman_index++] = ((code & mask) >> (length - 1 - i)) ? '1' : '0'; // translate character to binary
            mask >>= 1;
        }
    }

    return huffman; // return tree + '\n' + huffman code
}

char *huffman_decode(size_t len, const char data[len]) {
    char *buf = malloc(BUF_LENGTH); // save enough space for up to BUF_LENGTH characters
    int index = 0;
    size_t seperator = 0;

    if (!buf) {
        perror("Memory Error: Buffer could not be allocated");
        return NULL;
    }

    //find seperator in data of tree and decoding string
    for (size_t i = 0; i < len; i++) {
        if (data[i] == '\n') {
            seperator = i;
            break;
        }
    }

    //nothing to decode or no new line in data
    if (seperator == 0) {
        return buf;
    }

    //build tree from data
    int cur[1] = {0};
    Node *tree_root = decode_tree(&data[0], cur);

    // print (for debugging)
    printf("%sRebuilding tree%s\n", CYAN, WHITE);
    print_tree_inorder(tree_root);
    printf("\n\n");

    Node *pointer = tree_root;
    for (size_t i = seperator + 1; i < len; i++) {
        if (data[i] == '0') {
            pointer = pointer->left;
            if (pointer->left == NULL && pointer->right == NULL) {
                buf[index++] = pointer->character;
                pointer = tree_root;
            }
        } else if (data[i] == '1') {
            pointer = pointer->right;
            if (pointer->left == NULL && pointer->right == NULL) {
                buf[index++] = pointer->character;
                pointer = tree_root;
            }
        }
    }

    return buf;
}
