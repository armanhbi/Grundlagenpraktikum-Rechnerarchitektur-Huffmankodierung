#include "helper.h"

void file_error(FILE *fd, char *msg) {
    perror(msg);
    fclose(fd);
    exit(EXIT_FAILURE);
}

uint8_t fast_log2(int binary) {
    if (binary == 0 || binary == 1)
        return 1;
    if (binary == 2 || binary == 3)
        return 2;
    if (binary >= 4 && binary <= 7)
        return 3;
    if (binary >= 8 && binary <= 15)
        return 4;
    if (binary >= 16 && binary <= 31)
        return 5;
    if (binary >= 32 && binary <= 63)
        return 6;
    if (binary >= 64 && binary <= 127)
        return 7;
    if (binary >= 128 && binary <= 256)
        return 8;
    return -1;
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

void print_binary_with_max(uint64_t integer) {
    uint64_t mask = 0x8000000000000000;
    printf(MAGENTA);
    for (int i = 0; i < mask; i++) {
        putchar((integer & mask) ? '1' : '0');
        mask >>= 1;
    }
    printf(WHITE);
}