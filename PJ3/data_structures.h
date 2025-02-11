#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H


enum COLOR {WHITE, GRAY, BLACK};

typedef struct TAG_VERTEX {
    int index;      
    COLOR color;    
    double key;     
    int pi;         
    int position;   
} VERTEX, *pVERTEX;

typedef struct TAG_NODE {
    int index;      
    int u, v;       
    double w;       
    TAG_NODE *next; 
} NODE, *pNODE;

typedef VERTEX ELEMENT;
typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP {
    int capacity;   
    int size;       
    pELEMENT *H;    
} HEAP, *pHEAP;

typedef struct AdjacencyList {
    int numVertices;
    NODE** lists; 
}Graph;

typedef struct Stack {
    int top;          
    int capacity;     
    pVERTEX* elements; 
} STACK;




#endif

