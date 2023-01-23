/* Sudhanshu Patel sudhanshuptl13@gmail.com */
/*
Min Heap implementation in c
*/

#include "heap.h"

//int main() {
//    int i;
//    Heap *heap = create_heap(HEAP_SIZE, 0); //Min Heap
//    if (heap == NULL) {
//        printf("__Memory Issue____\n");
//        return -1;
//    }
//
//    for (i = 9; i > 0; i--)
//        insert(heap, i);
//
//    print(heap);
//
//    for (i = 9; i >= 0; i--) {
//        printf(" Pop Minima : %d\n", pop_min(heap));
//        print(heap);
//    }
//    return 0;
//}

Heap *create_heap(int capacity) {
    Heap *h = (Heap *) malloc(sizeof(Heap)); //one is number of heap

    //check if memory allocation is fails
    if (h == NULL) {
        printf("Memory Error!");
        return NULL;
    }
    h->count = 0;
    h->capacity = capacity;
    h->arr = malloc(capacity * sizeof(Node*)); //size in bytes

    //check if allocation succeed
    if (h->arr == NULL) {
        printf("Memory Error!");
        return NULL;
    }
    return h;
}

void insert(Heap *h, Node *node) {
    if (h->count < h->capacity) {
        h->arr[h->count] = node;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h, int index) {
    Node *tmp;
    int parent_node = (index - 1) / 2;

    if (h->arr[parent_node]->frequency > h->arr[index]->frequency) {
        //swap and recursive call
        tmp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = tmp;
        heapify_bottom_top(h, parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node) {
    int left = parent_node * 2 + 1;
    int right = parent_node * 2 + 2;
    int min;
    Node *tmp;

    if (left >= h->count || left < 0)
        left = -1;
    if (right >= h->count || right < 0)
        right = -1;

    if (left != -1 && h->arr[left]->frequency < h->arr[parent_node]->frequency)
        min = left;
    else
        min = parent_node;
    if (right != -1 && h->arr[right]->frequency < h->arr[min]->frequency)
        min = right;

    if (min != parent_node) {
        tmp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = tmp;

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

Node *pop_min(Heap *h) {
    Node *pop;
    if (h->count == 0) {
        printf("\nHeap is empty\n");
        return NULL;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count - 1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

void print(Heap *h) {
    int i;
    printf("Print Heap\n");
    for (i = 0; i < h->count; i++) {
        printf("-> Char '%c' mit freq '%d'", h->arr[i]->character, h->arr[i]->frequency);
    }
    printf("->__/\\__\n");
}