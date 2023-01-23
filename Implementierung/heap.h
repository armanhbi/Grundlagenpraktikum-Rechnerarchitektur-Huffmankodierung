#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define HEAP_SIZE 128

struct Heap {
    Node **arr;
    int count;
    int capacity;
};
typedef struct Heap Heap;

Heap *create_heap(int capacity);
void insert(Heap *h, Node *node);

Node *pop_min(Heap *h);
void print(Heap *h);

void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);

#endif