
#include "main.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s flag <FileI> <FileO>\n", argv[0]);
        return -1;
    }

    int flag = atoi(argv[1]);

    char command[100];
    int operationStatus;
    double position, key;
    
    HEAP *heap = NULL;

    while (1) {
        operationStatus = nextInstruction(command,position, key);

        if (operationStatus == 0) {
            fprintf(stdout, "Warning: Invalid instruction: %s\n", command);
            continue;
        }
		
		if (strcmp(command, "Stop") == 0){
			fprintf(stdout,"Instruction: %s\n", command);
			break;
			
		}else if (strcmp(command, "Print") == 0){
			fprintf(stdout,"Instruction: Print\n");
			if(!heap){
				fprintf(stderr,"Error: heap is NULL\n");
			}
			printHeap(heap);
			
		}else if (strcmp(command, "Write") == 0) {
		    fprintf(stdout, "Instruction: %s\n", command);
		    if (!heap) {
		        fprintf(stderr, "Error: heap is NULL\n");
		    } else {
		        FILE* outputFile = fopen(argv[3], "w");
		        if (!outputFile) {
		            fprintf(stderr, "Error: Cannot open output file %s for writing\n", argv[3]);
		        } else {
		        	fprintf(outputFile, "%d\n", heap->size);
		            for (int i = 0; i < heap->size; i++) {
		                fprintf(outputFile, "%lf\n", heap->H[i]->key);
		            }
		            fclose(outputFile);
		        }
		    }
		}

		else if (strcmp(command, "Read") == 0) {
		    fprintf(stdout, "Instruction: %s\n", command);
		
		    if (!heap) {
		        fprintf(stderr, "Error: heap is NULL\n");
		        continue;
		    }
		
		    FILE *inputFile = fopen(argv[2], "r");
		    if (!inputFile) {
		        fprintf(stderr, "Error: Cannot open input file %s for reading\n", argv[2]);
		        continue;
		    }
		
		    int n;
		    if (fscanf(inputFile, "%d", &n) != 1) {
		        fprintf(stderr, "Error: Failed to read the number of elements\n");
		        fclose(inputFile); 
		        continue;
		    }
		
		    if (heap->capacity < n) {
		        fprintf(stderr, "Error: heap's capacity is too small. Needed: %d, Available: %d\n", n, heap->capacity);
		        fclose(inputFile);
		        continue;
		    }
		
		    for (int i = 0; i < n; i++) {
		        double key;
		        if (fscanf(inputFile, "%lf", &key) != 1) {
		            fprintf(stderr, "Error: Failed to read key value\n");
		            break; 
		        }
		        heap->H[i] = (ELEMENT*)malloc(sizeof(ELEMENT));
		        if (!heap->H[i]) {
		            fprintf(stderr, "Error: Memory allocation failed\n");
		            break;
		        }
		        heap->H[i]->key = key;
		    }
		    heap->size = n;
		
		    if (!isValidMinHeap(heap->H, heap->size)) {
		        if (flag == 2 || flag == 3) {
		            fprintf(stdout, "Input array is NOT a MinHeap\n");
		            fprintf(stdout, "Call BuildHeap\n");
		        }
		        buildHeap(heap, flag);
		    }
		
		    fclose(inputFile); 
		}
		else if (strcmp(command, "Init") == 0){

			fprintf(stdout,"Instruction: %s %d\n", command, (int)position);
			heap = initialize(position);
			
		}else if (strcmp(command, "Insert") == 0) {
		    fprintf(stdout, "Instruction: %s %lf\n", command, position); 
		    if (!heap) {
		        fprintf(stderr, "Error: heap is NULL\n");
		    } else {
		        
		        if (heap->size >= heap->capacity) {
			        fprintf(stderr,"Error: heap is full\n");
			        continue;
			    }
		        
		        ELEMENT* newElement = (ELEMENT*)malloc(sizeof(ELEMENT));
		        if (newElement == NULL) {
		            fprintf(stderr, "Error: Memory allocation failed\n");
		        } else {
		        	int location = -1;
		            newElement->key = position; 
		            insert(heap, newElement, location);
		            location += 1;
		            if(flag == 1 || flag == 3){
		            	fprintf(stdout,"Element with key %lf inserted at location %d of the heap array\n", position, location  );
					}else{
						fprintf(stdout,"Element with key %lf inserted into the heap\n", position);	
					}
		            
		            
		        }
		    }
		}
		else if (strcmp(command, "DecreaseKey") == 0) {
			
		    int indexE = (int)position; 
		    double newKey = key;
		    fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", indexE, newKey);
		    indexE = indexE -1;
		    if (heap == NULL) {
		        fprintf(stderr, "Error: heap is NULL\n");
		    } else if (heap->size == 0) {
		        fprintf(stderr, "Error: heap is empty\n");
		    } else if (indexE < 0 || indexE >= heap->size || heap->H[indexE]->key <= newKey) {
		        fprintf(stderr, "Error: invalid call to DecreaseKey %lf\n",heap->H[indexE]->key);
		    } else {
		        decreaseKey(heap, indexE, newKey);
		        
		    }
		    
		}else if (strcmp(command, "ExtractMin") == 0) {
			
			int heapifyCalls = 0;
			
		    fprintf(stdout, "Instruction: ExtractMin\n");
		    if (!heap) {
		        fprintf(stderr, "Error: heap is NULL\n");
		    } else if (heap->size == 0) {
		        fprintf(stderr, "Error: heap is empty\n");
		    } else {
		        ELEMENT* minElement = extractMin(heap, heapifyCalls );
		        
		        if (flag == 2 || flag == 3) {
		        	
		            fprintf(stdout, "Element with key %lf extracted from the heap\n", minElement->key);
		            if(heap -> size ==0)
		            	heapifyCalls = 1;
					fprintf(stdout,"Number of Heapify calls triggered by ExtractMin: %d\n", heapifyCalls);
		        } else {
		            fprintf(stdout, "Element with key %lf extracted from the heap\n", minElement->key);
		        }
		        
		        free(minElement); 
		    }
		}

    }

    fclose(stdin);
    return 0;
}

