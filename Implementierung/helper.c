#include "helper.h"

void file_error(FILE *fd, char *msg) {
    perror(msg);
    fclose(fd);
    exit(EXIT_FAILURE);
}

uint8_t createMask(int number) {
    uint8_t mask = 0;
    for (int i = 0; i < number; i++) {
        mask <<= 1;
        mask++;
    }
    return mask;
}

void print_binary(char integer) {
    uint64_t mask = 0x80;
    uint8_t no_leading_zero = 0;
    printf(MAGENTA);
    for (int i = 0; mask; i++) {
        uint8_t bit_set = integer & mask;

        if (bit_set)
            no_leading_zero = 1;
        if (no_leading_zero)
            putchar(bit_set ? '1' : '0');
        mask >>= 1;
    }
    if (!no_leading_zero) {
        putchar('0');
    }
    printf(WHITE);
}