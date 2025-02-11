
#include "main.h"
#include "graph.h"
#include "heap.h"
#include "stack.h"
#include "util.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 4 ) {
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
        return -1;
    }

    char* inputFile = argv[1];
    char* graphType = argv[2];
    int flag = atoi(argv[3]);

    if ((strcmp(graphType, "DirectedGraph") != 0 && strcmp(graphType, "UndirectedGraph") != 0) || (flag != 1 && flag != 2)) {
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <Flag>\n", argv[0]);
        return 0;
    }

	int graphTypeInt = 0;

	if(strcmp(graphType, "DirectedGraph") == 0){
		graphTypeInt = 1;
	}
	else if(strcmp(graphType, "UndirectedGraph") == 0){
		graphTypeInt = 2;
	}

    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open input file %s for reading\n", inputFile);
        return -1;
    }

    int numVertices, numEdges;
    
    if (fscanf(file, "%d %d", &numVertices, &numEdges) != 2) {
        fprintf(stderr, "Error: Failed to read the number of vertices and edges\n");
        fclose(file);
        return -1;
    }

    
    Graph* graph = createGraph(numVertices);
    pVERTEX vertexArray = (pVERTEX)malloc((numVertices + 1) * sizeof(VERTEX));

    
    for (int i = 0; i < numEdges; i++) {
        int index, u, v;
        double weight;
        if (fscanf(file, "%d %d %d %lf", &index, &u, &v, &weight) == 4) {
            addEdge(graph, index, u, v, weight, flag, graphTypeInt);
        } else {
            fprintf(stderr, "Error: Failed to read edge data correctly\n");
            freeGraph(graph);
            fclose(file);
            return -1;
        }
    }


    int source = 1;
    int destination = 3;

    int searchSource = -1;
    int searchDestination = -1;

    int wasSingleSource = 0;
    int wasSinglePair = 0;

    int operationStatus = 0;
    char command[100];
    
    while (1) {
        operationStatus = nextInstruction(command,source, destination);

        if (operationStatus == 0) {
            fprintf(stderr, "Error: Invalid instruction.\n");
            continue;
        }

		if (strcmp(command, "Stop") == 0){
			break;
			
		}else if (strcmp(command, "PrintADJ") == 0){
			printGraph(graph);
		}else if (strcmp(command, "SingleSource") == 0) {
            if(source > numVertices){
                continue;
            }
            reinitializeVertexArray(vertexArray, numVertices);
            dijkstra(graph, source, vertexArray);
            wasSingleSource = 1;
            wasSinglePair = 0;
            searchSource = source;
		}else if (strcmp(command, "SinglePair") == 0) {
            if(source > numVertices){
                continue;
            }
            reinitializeVertexArray(vertexArray, numVertices);
            dijkstraToDestination(graph, source, destination, vertexArray);
            wasSinglePair = 1;
            wasSingleSource = 0;
            searchSource = source;
            searchDestination = destination;
        }else if(strcmp(command, "PrintLength") == 0){
        	if(wasSingleSource == 1){
                if(searchSource == source){
                    if(destination > numVertices || vertexArray[destination].key == DBL_MAX){
                        fprintf(stdout, "There is no path from %d to %d.\n",source, destination);
                        continue;
                    }
                    fprintf(stdout,"The length of the shortest path from %d to %d is: %8.2lf\n", source, destination, vertexArray[destination].key);
                }
        	}else if(wasSinglePair == 1){
                if(searchSource == source && searchDestination == destination){
                    fprintf(stdout,"The length of the shortest path from %d to %d is: %8.2lf\n", source, destination, vertexArray[destination].key);
                }
            }else{
                fprintf(stderr, "Error: Invalid instruction.\n");
            }
        }else if(strcmp(command, "PrintPath") == 0){
        	if(wasSingleSource == 1){
                if(searchSource == source){
                    printShortestPath(graph, source, destination, vertexArray);
                }
        	}else if(wasSinglePair == 1){
                if(searchSource == source && searchDestination == destination){
                    printShortestPath(graph, source, destination, vertexArray);
                }
            }else{
                fprintf(stderr, "Error: Invalid instruction.\n");
            }
        }
    }

    
    freeGraph(graph);
    fclose(file);

    return 0;
}


