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

void print_binary(char integer, uint8_t length) {
    printf(MAGENTA);

    uint64_t mask = 1 << (length - 1);

    for (int i = 0; mask; i++) {
        putchar(((integer & mask) >> (length - 1 - i)) ? '1' : '0');
        mask >>= 1;
    }

    printf(WHITE);
}