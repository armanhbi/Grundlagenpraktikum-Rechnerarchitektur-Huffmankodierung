#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *read_data(const char *path) {
    FILE *fd;
    char buf[32]; // A maximum of n characters

    fd = fopen(path, "r");

    if (fd == NULL) { // file does not exist or other error
        fprintf(stderr, "An error occured while opening file %s! (Does it exist?)", path);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fd, "%s", buf) == 1) { // fscanf thows an error
        printf("Inhalt: %s\n", buf);

        // WEITER VERARBEITUNG

        fclose(fd);
    }

    fprintf(stderr, "An error occured while reading the file %s! (Is it in the right format?)", path);

    fclose(fd);
}

bool write_data(const char *path, char *result) {
    return EXIT_FAILURE;
}