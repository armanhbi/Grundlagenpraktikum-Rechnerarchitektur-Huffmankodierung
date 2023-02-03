#include "huffman.h"

uint32_t encode_tree(Node *tree, char *buffer, uint32_t *index) {
    if (tree->right == NULL && tree->left == NULL) { // node with valid character was reached
        char character = tree->character;
        buffer[(*index)++] = '1'; // '1' meaning an 8 bit character will follow
        print("1 ");
        print("%c (", character);
        for (uint8_t i = 9; i > 1; i--) {
            char c = (character & 0x80) >> 7 ? '1' : '0'; // bithack to get the first bit of the character
            buffer[(*index)++] = c; // write character bit for bit into the buffer
            character <<= 1;
            put_chr(c);
        }
        print(") ");
        return 0; // irrelevant: gets ignored in rec use
    }
    buffer[(*index)++] = '0';
    print("0 ");
    encode_tree(tree->left, buffer, index); // adding a '0' everytime it moves further down and do recursion
    encode_tree(tree->right, buffer, index);
    return *index; // return length of the buffer
}

Node *decode_tree(const char *compressed, uint32_t *index) {
    Node *cur_node = create_node('\0', 0, NULL, NULL); // Create the upper node (always \0)

    if (!cur_node)
        return NULL;

    if (compressed[*index] != '\n') { // iterate through the buffer
        if (compressed[*index] == 49) { // ascii for '1' (8 bit character follows)
            char character = '\0';
            for (uint8_t i = 1; i < 9; i++) {
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
    }
    return cur_node; // return upper root node/tree
}

char *huffman_encode(size_t len, const char data[len]) {
    if (len == 0) {
        perror("HuffmanException: Der String zum encoden ist leer");
        return NULL;
    }

    uint16_t table[HEAP_SIZE] = {0}; // create table (same as extended unicode table (8 bits))

    // COUNT OCCURRENCES OF LETTERS

    for (size_t i = 0; i < len; i++) { // Go through input string O(n)
        table[(uint8_t) data[i]] += 1; // increment for every following letter (counting appearance)
    }

    // FILL HEAP

    Heap *heap = create_heap(HEAP_SIZE); // Create Min Heap
    if (!heap)
        return NULL;

    print("%sHäufigkeitsanalyse%s\n", CYAN, WHITE);
    for (uint16_t i = 0; i < HEAP_SIZE; i++) { // O(n log n)
        if (table[i] == 0) // if the value in the table is zero
            continue;

        Node *to_insert = create_node(i, table[i], NULL, NULL);
        if (!to_insert) {
            free_heap(heap);
            return NULL;
        }

        if (table[i] > 0) { // If frequency is > 0 add node to heap structure
            insert(heap, to_insert); // O(log n)
        }
    }

    if (heap->count == 1) {  // In the case that only one letter was given
        // pop the one element, create a null element and connect them both with a connecting node
        Node *only_element = pop_min(heap);
        print("'%c' kommt %s%d%s mal vor!\n", only_element->character, RED, only_element->frequency, WHITE);
        Node *null = create_node('\0', 0, NULL, NULL);
        Node *connector = create_node('\0', only_element->frequency, only_element, null);
        if (!null || !connector) { // If one of the nodes did not create (memory) return null
            free_heap(heap);
            return NULL;
        }
        insert(heap, connector); // Insert the connector back to the heap (it will get popped instantly)
    }

    while (heap->count > 1) { // Combine two smallest nodes (till only one left)  O(2n * log n) ?
        // Pop the two smallest nodes
        Node *min1 = pop_min(heap); // No null check -> count already checks condition
        Node *min2 = pop_min(heap);

        if (min1->character)
            print("'%c' kommt %s%d%s mal vor!\n", min1->character, RED, min1->frequency, WHITE);
        if (min2->character)
            print("'%c' kommt %s%d%s mal vor!\n", min2->character, RED, min2->frequency, WHITE);

        // Connect them with connecting node ('\0') and add frequencies together (min1 is left and min2 right tree branch)
        Node *connector = create_node('\0', min1->frequency + min2->frequency, min1, min2);

        if (!connector) {
            free_heap(heap);
            return NULL;
        }

        insert(heap, connector); // Insert connector node into heap O (log n)
    }

    Node *root = pop_min(heap); // Pop node which acts as the root

    free_heap(heap);

    print("\n%sTree creation%s\n", CYAN, WHITE);
    print_tree_inorder(root);
    print("\n\n");

    // Huffman Array with ==> compressed_tree + '\n' + huffman_code
    char *huffman = malloc(BUF_LENGTH * sizeof(char));

    if (!huffman) { // malloc check
        perror("Huffman Code memory space could not be allocated");
        free_node(root);
        free(huffman);
        return NULL;
    }

    // COMPRESS TREE ROOT

    print("%sCompressed tree%s\n", CYAN, WHITE);
    uint32_t index[1] = {0};
    uint32_t huffman_index = encode_tree(root, huffman, index);

    huffman[huffman_index++] = '\n'; // Add '\n'

    // TREE TO DICTIONARY

    // One array for the huffman code (lookup), one for the length of the code because binary saved (length)
    uint8_t length_table[HEAP_SIZE] = {0}; // savable in 3 bits -> max. huffman code length of ?
    uint32_t lookup_table[HEAP_SIZE] = {0};

    tree_to_dic(root, length_table, lookup_table, 0, 0);

    free_node(root);

    print("\n\n%sDictionary%s\n", CYAN, WHITE);
    for (uint16_t i = 0; i < HEAP_SIZE; i++) { // For every ascii character
        if (length_table[i] != 0) {
            print("'%c' -> ", i);
            print_binary(lookup_table[i], length_table[i]);
            print(" (Länge: %d)", length_table[i]);
            print("\n");
        }
    }
    print("\n");

    for (size_t i = 0; i < len; i++) {
        uint32_t code = lookup_table[(uint16_t) data[i]]; // Get huffman code as int
        uint8_t length = length_table[(uint8_t) data[i]]; // Get length of huffman code
        uint32_t mask = 1 << (length - 1); // mask moving from length to the end of the character (right side)

        for (uint32_t i = 0; mask; i++) {
            // If the Huffman Code is too long -> Error => Not really necessary because of check in read_data
            if (huffman_index > BUF_LENGTH) {
                perror("Der Huffman Code würde zu lang werden als Memory reserviert ist");
                free(huffman);
                return NULL;
            }
            huffman[huffman_index++] = ((code & mask) >> (length - 1 - i)) ? '1' : '0'; // translate character to binary
            mask >>= 1;
        }
    }

    return huffman; // return tree + '\n' + huffman code
}

char *huffman_decode(size_t len, const char data[len]) {
    if (len == 0) {
        perror("HuffmanException: Der String zum decoden ist leer");
        return NULL;
    }

    // save enough space for up to BUF_LENGTH characters (won't get more because it is checked in read_data and encode)
    char *buf = malloc(BUF_LENGTH);
    uint32_t index = 0;
    size_t separator = 0;

    if (!buf) { // malloc check
        perror("The buffer in decoding could not be allocated");
        return NULL;
    }

    // find separator in data of tree and decoding string
    for (size_t i = 0; i < len; i++) {
        if (data[i] == '\n') {
            separator = i;
            break;
        }
        if (data[i] != '0' && data[i] != '1') {
            fprintf(stderr, "DecodeException: There is an invalid character to decode -> %c", data[i]);
            free(buf);
            return NULL;
        }
    }

    if (separator == 0) { // nothing to decode or no new line in data
        perror("DecodeException: No newline was found in the decoded string");
        free(buf);
        return NULL;
    }

    // build tree from data
    uint32_t cur[1] = {0};
    Node *tree_root = decode_tree(&data[0], cur);

    if (!tree_root) {
        free(buf);
        return NULL;
    }

    print("%sRebuilding tree%s\n", CYAN, WHITE);
    print_tree_inorder(tree_root);
    print("\n\n");

    Node *pointer = tree_root;
    for (size_t i = separator + 1; i < len; i++) {
        if (data[i] == '0') {
            pointer = pointer->left;
            if (pointer->left == NULL && pointer->right == NULL) { // if node is a leaf/character
                buf[index++] = pointer->character; // add character to the buffer and reset pointer to root
                pointer = tree_root;
            }
        } else if (data[i] == '1') {
            pointer = pointer->right;
            if (pointer->left == NULL && pointer->right == NULL) { // same as above
                buf[index++] = pointer->character;
                pointer = tree_root;
            }
        }
    }

    if (pointer != tree_root) {
        perror("The Huffman Encoding is wrong");
        free(buf);
        free(tree_root);
        return NULL;
    }

    free(tree_root);
    return buf; // Return decodede huffman code as string
}
