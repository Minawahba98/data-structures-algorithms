#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

typedef struct {
    double key; 
} ELEMENT;

typedef struct {
    int capacity; 
    int size;     
    ELEMENT **H;  
} HEAP;

#endif

