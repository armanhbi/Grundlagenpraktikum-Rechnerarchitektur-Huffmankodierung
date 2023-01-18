#include "helper.h"

void file_error(FILE *fd, char *msg) {
    perror(msg);
    fclose(fd); // close fd if still open
    exit(EXIT_FAILURE);
}

void print_binary(char integer, uint8_t length) {
    printf(MAGENTA); // color code

    uint64_t mask = 1 << (length - 1); // mask starting from length to the end of character/integer (right side of binary)

    for (int i = 0; mask; i++) {
        putchar(((integer & mask) >> (length - 1 - i)) ? '1' : '0'); // translate character/integer to binary and print it
        mask >>= 1; // shift mask
    }

    printf(WHITE); // color code
}