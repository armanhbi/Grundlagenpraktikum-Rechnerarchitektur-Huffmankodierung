#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 1024

void file_error(FILE *fd, char *msg, char *arg) {
    fprintf(stderr, msg, arg);
    fclose(fd);
    exit(EXIT_FAILURE);
}

/**
 * @brief Reads the data from path into buf
 * @param path Path to the file
 * @return Returns the string saved in the file (Huffman encoding or normal ascii characters)
 */
char *read_data(char *path) {
    FILE *fd;
    char *buf = malloc(BUF_LENGTH); // save enough space for up to 1024 characters

    if (buf == NULL) { // if malloc did not work
        file_error(fd, "An error occurred while trying to allocate memory (malloc)\n", "");
    }

    fd = fopen(path, "r"); // open file with path and in reading mode

    if (fd == NULL) { // if opening the file did not work
        file_error(fd, "An error occurred while trying to get the file descriptor of %s! (Does it exist?)\n", path);
    }

    size_t i = 0;
    while (1) {
        char c = fgetc(fd);
        if (c == '\0' || feof(fd) || i == BUF_LENGTH)
            break;
        buf[i++] = c;
    }

    fclose(fd);
    return buf;
}

/**
 * @brief Saves the string in result into path
 * @param path where the result should be saved
 * @param result either Huffman encoding or normal ascii string
 * @return returns whether or not if worked
 */
void write_data(char *path, char *result) {
    FILE *fd;
    fd = fopen(path, "w");
    if (fd == NULL) {
        file_error(fd, "An error occurred while trying to allocate memory (malloc)\n", "");
    }

    printf("Result was saved in %s\n", path);

    // printf("Path %s\n", path);
    // printf("Result %s\n", result);

    if (fputs(result, fd) == EOF) {
        file_error(fd, "An error occurred while trying to save the string to %s\n", path);
    }
    fclose(fd);
}