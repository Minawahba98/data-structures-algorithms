#include "graph.h"
#include "heap.h"
#include "stack.h"

#include <stdio.h>
#include <float.h>
#include <stdlib.h>


Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->lists = (NODE**)malloc((numVertices + 1) * sizeof(NODE*)); 

    for (int i = 0; i <= numVertices; ++i) {
        graph->lists[i] = NULL; 
    }

    return graph;
}


void addEdge(Graph* graph, int index, int u, int v, double weight, int flag, int graphTypeInt) {
    
    NODE* newNodeU = (NODE*)malloc(sizeof(NODE));
    if (newNodeU == NULL) {
        fprintf(stderr, "Memory allocation failed for new node (u, v).\n");
        return; 
    }
    newNodeU->index = index;
    newNodeU->u = u;
    newNodeU->v = v;
    newNodeU->w = weight;
    newNodeU->next = NULL;

    
    insertNode(&(graph->lists[u]), newNodeU, flag);

    if (graphTypeInt == 2) { 
        
        NODE* newNodeV = (NODE*)malloc(sizeof(NODE));
        if (newNodeV == NULL) {
            fprintf(stderr, "Memory allocation failed for new node (v, u).\n");
            
            free(newNodeU);
            return;
        }
        newNodeV->index = index; 
        newNodeV->u = v;
        newNodeV->v = u;
        newNodeV->w = weight; 
        newNodeV->next = NULL;

        
        insertNode(&(graph->lists[v]), newNodeV, flag);
    }
}


void insertNode(NODE** list, NODE* node, int flag) {
    if (flag == 1) { 
        node->next = *list;
        *list = node;
    } else { 
        NODE** ptr = list;
        while (*ptr) {
            ptr = &((*ptr)->next);
        }
        *ptr = node;
    }
}



void printGraph(Graph* graph) {
    for (int i = 1; i <= graph->numVertices; ++i) {
        NODE* temp = graph->lists[i];
        printf("ADJ[%d]:", i);
        while(temp != NULL) {
            printf("-->[%d %d: %4.2lf]",temp->u, temp->v, temp->w);
            temp = temp->next;
        }
        printf("\n");
    }
}


void freeGraph(Graph* graph) {
    for (int i = 0; i <= graph->numVertices; ++i) {
        NODE* current = graph->lists[i];
        while (current != NULL) {
            NODE* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->lists);
    free(graph);
}

void dijkstra(Graph* graph, int source, pVERTEX vertexArray) {
    HEAP* minHeap = initHeap(graph->numVertices);
    int* vertexVisited = new int[graph->numVertices];

    for (int i = 1; i <= graph->numVertices; i++) {
        vertexVisited[i] = 0;
        vertexArray[i].index = i;
        vertexArray[i].key = DBL_MAX;
        vertexArray[i].pi = -1;
        vertexArray[i].position = i; 
        if (i == source){
            vertexArray[i].key = 0;
            insertHeap(minHeap, &vertexArray[i]);
            vertexVisited[i] = 1;
        } 
        
    }

    while (!isHeapEmpty(minHeap)) {
        pVERTEX u = extractMinHeap(minHeap);
        NODE* adjList = graph->lists[u->index];
        while (adjList != NULL) {
            int v = adjList->v;
            if (vertexArray[v].key > u->key + adjList->w) {
                vertexArray[v].key = u->key + adjList->w;
                vertexArray[v].pi = u->index;
                decreaseKeyHeap(minHeap, vertexArray[v].position, vertexArray[v].key);
            }
            if(vertexVisited[v] == 0){
                insertHeap(minHeap, &vertexArray[v]);
                vertexVisited[v] = 1;
            }

            adjList = adjList->next;
            
        }
    }

    freeHeap(minHeap);
}

void printShortestPath(Graph* graph, int source, int destination, pVERTEX vertexArray) {
    if (vertexArray[destination].key == DBL_MAX) {
        printf("No path from %d to %d exists.\n", source, destination);
        return;
    }

    
    STACK* pathStack = createStack(graph->numVertices);

    
    int at = destination;
    while (at != source) {
        if (vertexArray[at].pi == -1) { 
            printf("There is no path from %d to %d.\n", source, destination);
            freeStack(pathStack);
            return;
        }
        push(pathStack, &vertexArray[at]);
        at = vertexArray[at].pi;
    }
    printf("The shortest path from %d to %d is:\n", source, destination);
    push(pathStack, &vertexArray[source]); 

    pVERTEX current = pop(pathStack);

    double edgeWeight = 0.00; 
    printf("[%d:%8.2lf]", current->index,edgeWeight); 
    while (!isStackEmpty(pathStack)) {
        printf("-->");
        pVERTEX next = pop(pathStack);
        
        
        
        NODE* temp = graph->lists[current->index];
        while (temp != NULL) {
            if (temp->v == next->index) {
                edgeWeight += temp->w;
                break;
            }
            temp = temp->next;
        }

        
        if (edgeWeight != DBL_MAX) {
            printf("[%d:%8.2lf]",  next->index,edgeWeight);
            if(isStackEmpty(pathStack)){
                printf(".");
            }
        } else {
            printf(" -- Missing edge to %d", next->index);
        }
        
        current = next; 
    }

    printf("\n");
    freeStack(pathStack);
}


void reinitializeVertexArray(pVERTEX vertexArray, int numVertices) {
    for (int i = 1; i <= numVertices; i++) {
        vertexArray[i].index = i;
        vertexArray[i].key = DBL_MAX;
        vertexArray[i].pi = -1;
        vertexArray[i].position = -1;
    }
}

void dijkstraToDestination(Graph* graph, int source, int destination, pVERTEX vertexArray) {
    HEAP* minHeap = initHeap(graph->numVertices);

    for (int i = 1; i <= graph->numVertices; i++) {
        vertexArray[i].index = i;
        vertexArray[i].key = DBL_MAX;
        vertexArray[i].pi = -1;
        vertexArray[i].position = i; 
        if (i == source) vertexArray[i].key = 0;
        insertHeap(minHeap, &vertexArray[i]);


    }




    while (!isHeapEmpty(minHeap)) {

        
        pVERTEX u = extractMinHeap(minHeap);
    // printf("7");
        
        
        if (u->index == destination) {
            break;
        }
    // printf("8");

        NODE* adjList = graph->lists[u->index];
        while (adjList != NULL) {
            int v = adjList->v;
            if (vertexArray[v].key > u->key + adjList->w) {
                vertexArray[v].key = u->key + adjList->w;
                vertexArray[v].pi = u->index;
    // printf("9");

                decreaseKeyHeap(minHeap, vertexArray[v].position, vertexArray[v].key);
    // printf("10");
            
            }
    // printf("11");

            adjList = adjList->next;
        }
    // printf("12");

    }
    // printf("13");

    
    // printf("14");
    
    
}
