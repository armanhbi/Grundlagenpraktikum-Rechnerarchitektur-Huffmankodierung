#include "input_output.h"

char *read_data(char *path) {
    FILE *fd = NULL;
    char *buf = malloc(BUF_LENGTH * sizeof(char)); // save enough space for up to 1024 characters

    if (!buf) { // if malloc did not work
        perror("Memory Error: Allocating memory for buffer to read file did not work as expected.\n");
        return NULL;
    }

    fd = fopen(path, "r"); // open file with path and in reading mode

    if (!fd) { // if opening the file did not work
        perror("File Error: Opening file did not work as expected (Does the file exist?).\n");
        return NULL;
    }

    uint32_t i = 0;
    while (1) {
        char c = fgetc(fd); // read each character individually
        if (c == '\0' || feof(fd) ||
            i == BUF_LENGTH) // end was hit or \0 was hit or text extended BUFFER LENGTH (should rarely happen)
            break;
        buf[i++] = c; // add it to the buffer
    }

    fclose(fd); // close file descriptor
    return buf;
}

void write_data(char *path, char *result) {
    print("\n");

    FILE *fd;
    fd = fopen(path, "w"); // open file with path as file descriptor
    if (!fd) { // fopen check
        perror("File Error: Opening file did not work as expected (Does the file exist?).\n");
        return;
    }

    print("%sResult was saved in '%s'%s\n", GREEN, path, WHITE); // print (for debugging)

    if (fputs(result, fd) == EOF) { // if error occurred in writing data (EOF is returned)
        perror("File Error: Saving string in file did not work as expected.\n");
        return;
    }

    fclose(fd); // close file descriptor
}