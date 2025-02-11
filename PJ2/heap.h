#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;


HEAP* initialize(int capacity);
void insert(HEAP *heap, ELEMENT *element,int& location);
ELEMENT* extractMin(HEAP *heap, int& heapifyCallCounter) ;
void decreaseKey(HEAP *heap, int index, double newValue);
void buildHeap(HEAP *heap,  int flag) ;
void minHeapify(HEAP *heap, int i, int& heapifyCallCounter);
void printHeap(HEAP *heap);
int isValidMinHeap(ELEMENT** array, int size);

#endif // HEAP_H

