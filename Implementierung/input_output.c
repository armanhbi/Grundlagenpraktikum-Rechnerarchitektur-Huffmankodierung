#include "input_output.h"

int is_dir(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

char *read_data(const char *path, uint32_t *length) {
    FILE *fd = NULL;
    char *buf = calloc(BUF_LENGTH, sizeof(char)); // save enough space for up to BUF_LENGTH characters

    if (!buf) { // if calloc did not work
        perror("Buffer for reading a file could not be allocated");
        return NULL;
    }

    if (is_dir(path)) {
        perror("The path is a directory");
        return NULL;
    }

    fd = fopen(path, "rb"); // open file with path and in reading mode

    if (!fd) { // if opening the file did not work
        perror("Opening a file did not work as expected");
        return NULL;
    }

    uint32_t i = 0;
    while (1) {
        char c = fgetc(fd); // read each character individually
        if (c == '\0' || feof(fd)) // end was hit or \0 was hit or text extended BUFFER LENGTH (should rarely happen)
            break;
        buf[i++] = c; // add it to the buffer
        if (i == (BUF_LENGTH - 1)) {
            perror("Der eingegebene String ist zu lang! (Max: 131072 Zeichen)");
            return NULL;
        }
    }
    *length = i;
    buf[i++] = '\0';

    fclose(fd); // close file descriptor
    return buf;
}

int write_data(const char *path, char *result) {
    print("\n");

    if (is_dir(path)) {
        perror("The path is a directory");
        return 1;
    }

    FILE *fd;
    fd = fopen(path, "w"); // open file with path as file descriptor
    if (!fd) { // fopen check
        perror("File does not exist");
        return 1;
    }

    print("%sResult was saved in '%s'%s\n", GREEN, path, WHITE); // print (for debugging)

    if (fputs(result, fd) == EOF) { // if error occurred in writing data (EOF is returned)
        perror("Writing string in file did not work as expected");
        return 1;
    }

    fclose(fd); // close file descriptor
    return 0;
}
