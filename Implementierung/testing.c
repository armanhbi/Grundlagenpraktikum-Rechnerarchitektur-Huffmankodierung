#include "testing.h"

const char *test_array[] = {"Hallo,",
                            "Wiegehts?",
                            "",
                            "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGFFFFiiiiiiiiiiiiiiiiiiii",
                            "x",
                            "        "
};

const char *test_paths[] = {"txt/in.txt",
                            "txt/in2.txt",
                            "txt/in3.txt",
                            "txt/in4.txt",
                            //"txt/in5.txt",
                            "txt/info.txt",
};

void test_case(const char *test_string) {
    char *encode = huffman_encode(strlen(test_string), test_string);
    if (!encode) {
        printf("Test failed! Encoded did not work correctly\n");
        return;
    }
    char *decode = huffman_decode(strlen(encode), encode);
    if (!decode || strcmp(decode, test_string) == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test FAILED!\n");
        //printf("Test FAILED! \nString expected:\n%s\nString returned:\n%s\n", test_string, decode);
    }
}

void test_case_path(const char *test_path) {
    char *data;
    uint32_t data_length[1] = {0};
    data = read_data(test_path, data_length); // Read string out of input file

    if (data == NULL) {
        printf("Test failed! File could not be loaded\n");
        return;
    }


    if (*data_length == 0) {
        printf("Test FAILED! Length of data is empty\n");
        return;
    }

    char *encode = huffman_encode(*data_length, data);
    if (!encode) {
        printf("Test FAILED! Encoded did not work correctly\n");
        return;
    }

    char *decode = huffman_decode(strlen(encode), encode);

    if (!decode || strcmp(decode, data) == 0) {
        printf("Test passed!\n");
    } else {
        printf("Test FAILED!\n");
        //printf("Test failed! \nString expected:\n%s\nString returned:\n%s\n", data, decode);
    }
}

void test_all() {
    size_t length_array = sizeof(test_array) / sizeof(test_array[0]);
    printf("Länge vom Testarray: %zu\n", length_array);
    for (size_t i = 0; i < length_array; i++) {
        printf("%zu -> ", i);
        test_case(test_array[i]);
    }

    printf("\n");

    size_t length_paths = sizeof(test_paths) / sizeof(test_paths[0]);
    printf("Länge vom Patharray: %zu\n", length_paths);
    for (size_t i = 0; i < length_paths; i++) {
        printf("%zu -> ", i);
        test_case_path(test_paths[i]);
    }

}
