#include "input_output.h"

char *read_data(char *path) {
    FILE *fd;
    char *buf = malloc(BUF_LENGTH); // save enough space for up to 1024 characters

    if (buf == NULL) { // if malloc did not work
        file_error(fd, "An error occurred while trying to allocate memory (malloc).\n");
    }

    fd = fopen(path, "r"); // open file with path and in reading mode

    if (fd == NULL) { // if opening the file did not work
        file_error(fd, "An error occurred while trying to get the file descriptor. (Does it exist?)\n");
    }

    uint16_t i = 0;
    while (1) {
        char c = fgetc(fd); // read each character individually
        if (c == '\0' || feof(fd) || i == BUF_LENGTH) // end was hit or \0 was hit or text extended BUFFER LENGTH (should rarely happen)
            break;
        buf[i++] = c; // add it to the buffer
    }

    fclose(fd); // close file descriptor
    return buf;
}

void write_data(char *path, char *result) {
    printf("\n"); // print (for debugging)

    FILE *fd;
    fd = fopen(path, "w"); // open file with path as file descriptor
    if (fd == NULL) { // fopen check
        file_error(fd, "An error occurred while trying to allocate memory (malloc).\n");
    }

    printf("%sResult was saved in '%s'%s\n", GREEN, path, WHITE); // print (for debugging)

    if (fputs(result, fd) == EOF) { // if error occurred in writing data (EOF is returned)
        file_error(fd, "An error occurred while trying to save the string.\n");
    }

    fclose(fd); // close file descriptor
}