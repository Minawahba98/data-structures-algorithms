/*
 * Summary:
 * This is the implementation file for a linked list data structure.
 * It contains functions for appending, deleting, and inserting nodes in the list.
 */

#include "list_read.h"
#include "list_write.h"
#include <stdio.h>
#include <stdlib.h>

// Function to append a node at the tail of the list
NODE *listAppend(LIST *pLIST, double key) {
    NODE *pNODE;
    
    // Allocate memory for a new node
    pNODE = (NODE *)malloc(sizeof(NODE));
    if (!pNODE) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    
    // Set the key field of the new node to the given key
    pNODE->key = key;
    pNODE->next = NULL;
    
    if (pLIST->head == NULL) {
        // The list is empty, so the new node becomes both the head and tail
        pLIST->head = pNODE;
        pLIST->tail = pNODE;
    } else {
        // Append the new node at the tail of the list
        pLIST->tail->next = pNODE;
        pLIST->tail = pNODE;
    }
    
    fprintf(stdout, "Node with key %.6f appended\n", key);
    return pNODE;
}

// Function to delete a node with a given key from the list
NODE *listDelete(LIST *pLIST, double key) {
    NODE *pNODE = pLIST->head;
    NODE *prevNODE = NULL;
    
    // Search for the node with the given key
    while (pNODE != NULL && pNODE->key != key) {
        prevNODE = pNODE;
        pNODE = pNODE->next;
    }
    
    if (pNODE == NULL) {
        // Node with key not found
        fprintf(stdout, "Query %.6f NOT FOUND in list\n", key);
        fprintf(stdout, "There is no node with key %.6f in list\n", key);
    } else {
        // Node with key found
        fprintf(stdout, "Query %.6f FOUND in list\n", key);
        if (prevNODE == NULL) {
            // Node is the head of the list
            pLIST->head = pNODE->next;
        } else {
            // Node is not the head of the list
            prevNODE->next = pNODE->next;
        }
        
        // If the node is the tail of the list, update the tail pointer
        if (pNODE == pLIST->tail) {
            pLIST->tail = prevNODE;
        }
        
        // Free the memory for the deleted node
        free(pNODE);
        fprintf(stdout, "Node with key %.6f deleted\n", key);
    }
    
    return NULL;
}

// Function to insert a new node at the head of the list
NODE *listInsert(LIST *pLIST, double key) {
    NODE *pNODE;
    
    // Allocate memory for a new node
    pNODE = (NODE *)malloc(sizeof(NODE));
    if (!pNODE) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    
    // Set the key field of the new node to the given key
    pNODE->key = key;
    
    // Insert the new node at the head of the list
    pNODE->next = pLIST->head;
    pLIST->head = pNODE;
    
    fprintf(stdout, "Node with key %.6f inserted\n", key);
    return pNODE;
}