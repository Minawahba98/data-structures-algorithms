#include "heap.h"


HEAP* initialize(int capacity) {
    HEAP* heap = new HEAP;
    heap->capacity = capacity;
    heap->size = 0;
    heap->H = new ELEMENT*[capacity];
    return heap;
}

void insert(HEAP *heap, ELEMENT *element, int& location) {
    
    
    heap->size++;
    int i = heap->size - 1;
    heap->H[i] = element;

    while (i != 0 && heap->H[(i - 1) / 2]->key > heap->H[i]->key) {
        std::swap(heap->H[i], heap->H[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    
    location = i;
}


ELEMENT* extractMin(HEAP *heap, int& heapifyCallCounter) {
	heapifyCallCounter = 0; 
    if (heap->size == 1) {
        heap->size--;
        return heap->H[0];
    }

    
    ELEMENT* root = heap->H[0];
    heap->H[0] = heap->H[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0, heapifyCallCounter);

    return root;
}

void decreaseKey(HEAP *heap, int index, double newValue) {
    heap->H[index]->key = newValue;
    while (index != 0 && heap->H[(index - 1) / 2]->key > heap->H[index]->key) {
        std::swap(heap->H[index], heap->H[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}


void buildHeap(HEAP *heap,  int flag) {
	int heapifyCallCounter = 0;
    int startIndex = (heap->size / 2) - 1; 
    for (int i = startIndex; i >= 0; i--) {
        minHeapify(heap, i, heapifyCallCounter);
    }
    
    if (flag == 2 || flag == 3) {
        fprintf(stdout, "Number of Heapify calls triggered by BuildHeap: %d\n", heapifyCallCounter );
    }
}


void minHeapify(HEAP *heap, int i, int& heapifyCallCounter) {
	heapifyCallCounter++;
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    
    if (l < heap->size && heap->H[l]->key < heap->H[smallest]->key)
        smallest = l;

    
    if (r < heap->size && heap->H[r]->key < heap->H[smallest]->key)
        smallest = r;

    
    if (smallest != i) {
        swap(heap->H[i], heap->H[smallest]);
        minHeapify(heap, smallest, heapifyCallCounter);
    }
}

void printHeap(HEAP *heap){
	fprintf(stdout,"%d\n", heap->size);
	for(int i=0; i < heap->size ; i++){
		fprintf(stdout,"%lf\n",heap->H[i]->key);
	}
}

int isValidMinHeap(ELEMENT** array, int size) {
    
    
    for (int i = 0; i <= (size - 2) / 2; i++) {
        
        if (2 * i + 1 < size && array[i]->key > array[2 * i + 1]->key) {
            return 0; 
        }
        
        if (2 * i + 2 < size && array[i]->key > array[2 * i + 2]->key) {
            return 0;
        }
    }
    return 1;
}

