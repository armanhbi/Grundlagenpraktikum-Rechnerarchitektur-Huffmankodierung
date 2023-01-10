#ifndef INPUT_OUTPUT_H_
#define INPUT_OUTPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

#define BUF_LENGTH 1024

void file_error(FILE *fd, char *msg);

char *read_data(char *path);
void write_data(char *path, char *result);

char *read_binary(char *path);
void write_binary(char *path, char *result);

#endif