#include "heap.h"

Heap *create_heap(int capacity) {
    Heap *heap = (Heap *) calloc(1, sizeof(Heap)); // Allocating memory for the heap

    if (!heap) { // check calloc of heap
        perror("HeapException: Memory for the heap could not be allocated");
        return NULL;
    }

    heap->count = 0;
    heap->capacity = capacity;
    heap->arr = calloc(capacity, sizeof(Node *)); // Allocate memory for every pointer (~64 bit * 256 = 1-2kb)

    if (!heap->arr) { // check calloc of array
        perror("HeapException: Memory for the array in a heap could not be allocated");
        return NULL;
    }

    return heap; // return empty heap
}

void insert(Heap *heap, Node *node) {
    if (heap->count < heap->capacity) { // if enough space is available (should always be true)
        heap->arr[heap->count] = node;
        heapify_bottom_top(heap, heap->count++); // Swift item to the top if necessary and inc. count
    }
}

void heapify_bottom_top(Heap *heap, int index) {
    Node *tmp;
    // Structure: Parent -> Child1 -> Child2 -> Child1 of 1 -> Child2 of 1 -> Child1 of 2 -> ...
    int parent_node_index = (index - 1) / 2;

    // If frequency of parent is higher than current child
    if (heap->arr[parent_node_index]->frequency > heap->arr[index]->frequency) {
        tmp = heap->arr[parent_node_index]; // swap parent and child
        heap->arr[parent_node_index] = heap->arr[index];
        heap->arr[index] = tmp;

        heapify_bottom_top(heap, parent_node_index); // recursive call with the same child but as parent now
    }
}

void heapify_top_bottom(Heap *heap, int parent_node) {
    int left_index = parent_node * 2 + 1;
    int right_index = parent_node * 2 + 2;
    int min_index;

    Node *tmp;

    if (left_index >= heap->count || left_index < 0) // If no childs or no parent
        left_index = -1;
    if (right_index >= heap->count || right_index < 0)
        right_index = -1;

    // Select min value between parent and child1/2
    if (left_index != -1 && heap->arr[left_index]->frequency < heap->arr[parent_node]->frequency)
        min_index = left_index;
    else
        min_index = parent_node;
    if (right_index != -1 && heap->arr[right_index]->frequency < heap->arr[min_index]->frequency)
        min_index = right_index;

    if (min_index != parent_node) { // If one of the children is the min value
        tmp = heap->arr[min_index]; // Swap the child with the parent
        heap->arr[min_index] = heap->arr[parent_node];
        heap->arr[parent_node] = tmp;

        heapify_top_bottom(heap, min_index); // recursive  call
    }
}

Node *pop_min(Heap *heap) {
    Node *to_pop;

    if (heap->count == 0) { // Empty heap
        perror("HeapException: Heap is empty");
        return NULL;
    }

    // replace first node (always smallest) by last and delete last
    to_pop = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->count];

    heapify_top_bottom(heap, 0); // Swift from top down to justify heap rule (see above)

    return to_pop;
}

void print_heap(Heap *heap) {
    print("Printing Heap\n");
    for (int i = 0; i < heap->count; i++) { // Go through heap
        print("-> ('%c' mit '%d')", heap->arr[i]->character, heap->arr[i]->frequency);
    }
    print("-> /\n");
}

void free_heap(Heap *heap) {
    for (int i = 0; i < heap->count; i++) { // Go through heap
        if (heap->arr[i]) { // if array element exists
            free(heap->arr[i]); // free array
        }
    }
    if (heap) // if heap structure exists, free it
        free(heap);
}
