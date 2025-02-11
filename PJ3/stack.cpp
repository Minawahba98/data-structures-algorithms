#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


STACK* createStack(int capacity) {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed for stack\n");
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1; 
    stack->elements = (pVERTEX*)malloc(capacity * sizeof(pVERTEX));
    if (stack->elements == NULL) {
        fprintf(stderr, "Memory allocation failed for stack elements\n");
        free(stack);
        return NULL;
    }
    return stack;
}


void freeStack(STACK* stack) {
    if (stack != NULL) {
        free(stack->elements);
        free(stack);
    }
}


int isStackEmpty(STACK* stack) {
    return stack->top == -1;
}


int isStackFull(STACK* stack) {
    return stack->top == stack->capacity - 1;
}


void push(STACK* stack, pVERTEX element) {
    if (isStackFull(stack)) {
        fprintf(stderr, "Push failed: stack is full\n");
        return;
    }
    stack->elements[++stack->top] = element;
}


pVERTEX pop(STACK* stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Pop failed: stack is empty\n");
        return NULL;
    }
    return stack->elements[stack->top--];
}


pVERTEX top(STACK* stack) {
    if (isStackEmpty(stack)) {
        fprintf(stderr, "Top failed: stack is empty\n");
        return NULL;
    }
    return stack->elements[stack->top];
}