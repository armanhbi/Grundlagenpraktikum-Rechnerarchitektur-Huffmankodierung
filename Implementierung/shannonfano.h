#ifndef VERGLEICHSIMPLEMENTIERUNG_H
#define VERGLEICHSIMPLEMENTIERUNG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "printer.h"

typedef struct Entry Entry;
struct Entry {
    char character;
    uint16_t frequency;
};

void recursive_encode(uint8_t start_index, uint8_t end_index, Entry *table, size_t length, uint32_t *lookup_table,
                      uint8_t *length_table);

char *shannonfano_encode(size_t len, const char data[len]);

#endif