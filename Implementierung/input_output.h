#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "helper.h"

char *read_data(char *path);
void write_data(char *path, char *result);

char *read_binary(char *path);
void write_binary(char *path, char *result);

#endif