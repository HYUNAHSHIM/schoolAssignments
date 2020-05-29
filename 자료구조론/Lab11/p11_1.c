#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Queue* Queue;
typedef struct _Graph* Graph;

struct _Graph {
	int size;
	int* node;
	int** matrix;
};

struct _Queue {
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);
void DeleteGraph(Graph G);
/*void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);*/

int main(int argc, char* argv[]) {

	FILE* fi = fopen(argv[1], "r");
	if (fi == NULL) {
		printf("There is no file : %s\n", argv[1]);
		exit(-1);
	}

	int length = 0;
	char num[100]="\0";
	
	int i = 0, j = 0, k=0;
	int* nod;
	fgets(num, 100, fi);
	nod = (int*)malloc(sizeof(int)*(strlen(num) / 2 ));
	for (i = 0; i < strlen(num)-1; i++) {
		if (num[i] != ' ') {
			nod[k] = num[i]-48;
			k++;
		}
	}
	
	Graph graph = CreateGraph(nod);

	for (i = 0; !feof(fi); i++) {
		int a, b;
		char tmp;
		fscanf(fi, "%d%c%d ", &a, &tmp, &b);
		InsertEdge(graph, a, b);
	}

	printf("  ");
	for (i = 0; i < graph->size; i++) {
		printf("%d ", graph->node[i]);
	}
	printf("\n");
	for (i = 0; i < graph->size; i++) {
		printf("%d ", graph->node[i]);
		for (j = 0; j < graph->size; j++) {
			printf("%d ", graph->matrix[i][j]);
		}
		printf("\n");
	}
	
	free(nod);
	return 0;
}

Graph CreateGraph(int* nodes) {
	int i = 0, j = 0;
	Graph G = (Graph)malloc(sizeof(struct _Graph));
	G->size = 0;
	for (i = 0; 0<=nodes[i]&&nodes[i]<=9; i++) {
		G->size++;
	}	
	G->matrix = (int**)malloc(sizeof(int*)*G->size);
	for (i = 0; i < G->size; i++) {
		G->matrix[i] = (int*)malloc(sizeof(int)*G->size);
	}
	for (i = 0; i < G->size; i++) {
		for (j = 0; j < G->size; j++) {
			G->matrix[i][j] = 0;
		}
	}
	G->node = (int*)malloc(sizeof(int)*G->size);
	for (i = 0; i < G->size; i++) {
		G->node[i] = nodes[i];
	}
	
	return G;
}

void InsertEdge(Graph G, int a, int b) {
	int i = 0, j = 0;
	for (i = 0; i < G->size; i++) {
		if (G->node[i] == a) {
			for (j = 0; j < G->size; j++) {
				if (G->node[j] == b) {
					G->matrix[i][j] = 1;
				}
			}
		}
	}
}

void DeleteGraph(Graph G) {
	free(G->matrix);
	free(G);
}
