#ifndef STACK_H
#define STACK_H

#include "data_structures.h" 


STACK* createStack(int capacity);        
void freeStack(STACK* stack);            
int isStackEmpty(STACK* stack);          
int isStackFull(STACK* stack);           
void push(STACK* stack, pVERTEX element); 
pVERTEX pop(STACK* stack);                
pVERTEX top(STACK* stack);                

#endif // STACK_H
