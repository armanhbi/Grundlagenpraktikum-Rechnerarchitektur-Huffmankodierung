#include "insertionsort.h"

// Used implementation from: https://www.mygreatlearning.com/blog/insertion-sort-algorithm/#:~:text=Insertion%20sort%20in%20c%20is,position%20in%20the%20sorted%20part.
// For own usage -> Change later to own sorting algorithm!!!

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int tmp = arr[i];
        int j = i - 1;

        while (tmp < arr[j] && j >= 0) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = tmp;
    }
}