#include <stdio.h>
#include <stdlib.h>

void print_error(char *msg) {
    perror(msg);
}

/**
 * @brief Turns an array of ascii characters into an savable Huffman coding
 * @param len Length of the inputted string
 * @param data Array of ascii characters
 * @return Returns a string consisting of binary code AND tree
 */
char* huffman_encode(size_t len, const char data[len]) {

    int *table = calloc(128, sizeof (int));

    if (!table) {
        print_error("Calloc did not work as expected\n");
        return "";
    }

    for (int i = 0; i < len; i++) {
        table[(int) data[i]] += 1;
    }

    for (int i = 0; i < 128; i++) {
        int frequency = table[i];
        if (frequency != 0)
            printf("Der '%c' kommt %d mal vor!\n", i, table[i]);
    }

    // free table

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
char* huffman_decode(size_t len, const char data[len]) {
    return "";
}

