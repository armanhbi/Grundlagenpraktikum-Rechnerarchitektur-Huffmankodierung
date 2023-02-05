/*
 * Sudhanshu Patel sudhanshuptl13@gmail.com
 * Modified Min Heap Implementation in C
 * https://gist.github.com/sudhanshuptl/d86da25da46aa3d060e7be876bbdb343
*/

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

// Creating heap structure with appropriate attributes
typedef struct Heap Heap;
struct Heap {
    Node **arr; // Array of node pointers
    int count; // Items currently in heap
    int capacity; // Items max. possible in heap
};

/**
 * @brief Creates empty heap structure with count, capacity and array of node pointers as attributes
 * @param capacity Number of max. heap elements
 * @return Pointer to heap structure
 */
Heap *create_heap(int capacity);

/**
 * @brief Inserts one node (pointer) into heap -> Justify heap rule
 * @param heap Pointer to heap to insert into
 * @param node Pointer to node to insert
 */
void insert(Heap *heap, Node *node);

/**
 * @brief Pop the minimum node element (lowest frequency) and give back
 * @param heap Pointer to heap to insert into
 * @return Pointer to node which is the minimum
 */
Node *pop_min(Heap *heap);

/**
 * @brief Justifies the heap rule ("sorted" binary tree), swifting from bottom to top
 * @param heap Pointer to heap to insert into
 * @param index Index to heapify from (from index to top)
 */
void heapify_bottom_top(Heap *heap, int index);

/**
 * @brief Justifies the heap rule ("sorted" binary tree), swifting from top to bottom
 * @param heap Pointer to heap to insert into
 * @param parent_node Index of parent_node to heapify from
 */
void heapify_top_bottom(Heap *heap, int parent_node);

/**
 * @brief Print heap structure
 * @param heap Pointer to heap to insert into
 */
void print_heap(Heap *heap);

/**
 * @brief Free heap structure
 * @param heap Pointer to heap to insert into
 */
void free_heap(Heap *heap);

#endif
