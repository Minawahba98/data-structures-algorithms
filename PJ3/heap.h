#ifndef HEAP_H
#define HEAP_H
#include "data_structures.h"

HEAP* initHeap(int capacity);
void insertHeap(HEAP *heap, pELEMENT element);
void decreaseKeyHeap(HEAP *heap, int position, double newKey);
pELEMENT extractMinHeap(HEAP *heap);
void minHeapify(HEAP *heap, int position);
void freeHeap(HEAP *heap);
void buildMinHeap(HEAP *heap);
int isHeapEmpty(HEAP* heap);

#endif // HEAP_H

