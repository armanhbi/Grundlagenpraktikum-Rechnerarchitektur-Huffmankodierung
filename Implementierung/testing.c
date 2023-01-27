#include "testing.h"

int testing(char* testString){
    char *encode = huffman_encode(strlen(testString), testString);
    char *decode = huffman_decode(strlen(encode), encode);
    if(strcmp(decode,testString) == 0){
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed! \nString expected:\n%s\nString returned:\n%s\n", testString, decode);
        return 1;
    }
}