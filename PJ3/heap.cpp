#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h> // For DBL_MAX

// Initializes a new heap with a given capacity
HEAP* initHeap(int capacity) {
    HEAP* heap = (HEAP*)malloc(sizeof(HEAP));
    if (!heap) {
        fprintf(stderr, "Memory allocation error during heap initialization.\n");
        return NULL;
    }

    heap->capacity = capacity;
    heap->size = 0;
    heap->H = (pELEMENT*)malloc((capacity + 1) * sizeof(pELEMENT)); // +1 if using 1-based indexing
    if (!heap->H) {
        fprintf(stderr, "Memory allocation error during heap array initialization.\n");
        free(heap);
        return NULL;
    }

    return heap;
}

// Inserts a new element into the heap
void insertHeap(HEAP *heap, pELEMENT element) {
    if (heap->size >= heap->capacity) {
        printf("Heap overflow cannot insert key.\n");
        return;
    }

    // Insert the new element at the end
    heap->size++;
    int i = heap->size;
    heap->H[i] = element;

    // Percolate up
    while (i > 1 && heap->H[i / 2]->key > heap->H[i]->key) {
        pELEMENT temp = heap->H[i];
        heap->H[i] = heap->H[i / 2];
        heap->H[i / 2] = temp;
        i = i / 2;
    }
}

// Decreases the key of an element in the heap
void decreaseKeyHeap(HEAP *heap, int position, double newKey) {
    if (position < 1 || position > heap->size || newKey > heap->H[position]->key) {
        return;
    }

    heap->H[position]->key = newKey;
    // Percolate up
    while (position > 1 && heap->H[position / 2]->key > heap->H[position]->key) {
        pELEMENT temp = heap->H[position];
        heap->H[position] = heap->H[position / 2];
        heap->H[position / 2] = temp;
        position = position / 2;
    }
}

// Extracts the element with the minimum key from the heap
pELEMENT extractMinHeap(HEAP *heap) {
    if (heap->size < 1) {
        printf("Heap underflow.\n");
        return NULL;
    }

    pELEMENT min = heap->H[1]; // Assuming 1-based indexing
    heap->H[1] = heap->H[heap->size];
    heap->size--;
    minHeapify(heap, 1);

    return min;
}

// Maintains the min-heap property by percolating down
void minHeapify(HEAP *heap, int position) {
    int left = 2 * position;
    int right = 2 * position + 1;
    int smallest = position;

    if (left <= heap->size && heap->H[left]->key < heap->H[smallest]->key) {
        smallest = left;
    }

    if (right <= heap->size && heap->H[right]->key < heap->H[smallest]->key) {
        smallest = right;
    }

    if (smallest != position) {
        pELEMENT temp = heap->H[position];
        heap->H[position] = heap->H[smallest];
        heap->H[smallest] = temp;
        minHeapify(heap, smallest);
    }
}

// Frees the memory allocated for the heap
void freeHeap(HEAP *heap) {
    for (int i = 1; i <= heap->size; i++) {
        free(heap->H[i]);
    }
    free(heap->H);
    free(heap);
}

// Builds a min-heap from an unsorted array
void buildMinHeap(HEAP *heap) {
    for (int i = heap->size / 2; i >= 1; i--) {
        minHeapify(heap, i);
    }
}

int isHeapEmpty(HEAP* heap) {
    return heap->size == 0;
}
