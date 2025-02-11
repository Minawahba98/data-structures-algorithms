#ifndef GRAPH_H
#define GRAPH_H

#include "data_structures.h"

Graph* createGraph(int numVertices);
void addEdge(Graph* graph, int index, int u, int v, double weight, int flag, int graphTypeInt);
void insertNode(NODE** list, NODE* node, int flag);
void printGraph(Graph* graph);
void freeGraph(Graph* graph);
void dijkstra(Graph* graph, int source, pVERTEX vertexArray);
void dijkstraToDestination(Graph* graph, int source, int destination, pVERTEX vertexArray);
void printShortestPath(Graph* graph, int source, int destination, pVERTEX vertexArray);
void reinitializeVertexArray(pVERTEX vertexArray, int numVertices);
#endif // GRAPH_H