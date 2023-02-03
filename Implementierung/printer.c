#include "printer.h"

unsigned int DEBUG_PRINT = 0;

void print_binary(char integer, uint8_t length) {
    print(MAGENTA); // color code

    // mask starting from length to the end of character/integer (right side of binary)
    uint64_t mask = 1 << (length - 1);

    for (uint8_t i = 0; mask; i++) {
        // translate character/integer to binary and print it
        put_chr(((integer & mask) >> (length - 1 - i)) ? '1' : '0');
        mask >>= 1; // shift mask
    }

    print(WHITE); // color code
}

void print(const char *format, ...) {
    if (DEBUG_PRINT) { // if flag to print is set
        va_list args; // Template: https://www.ozzu.com/wiki/504927/writing-a-custom-printf-wrapper-function-in-c
        va_start(args, format);
        vfprintf(stdout, format, args); // Printing to stdout
        va_end(args);
    }
}

void put_chr(char c) {
    if (DEBUG_PRINT)
        putchar(c);
}
