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
void Topsort(Graph G);
Queue MakeNewQueue(int X);
int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Dequeue(Queue Q);
void Enqueue(Queue Q, int X);
void DeleteQueue(Queue Q);
void MakeEmpty(Queue Q);

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

	Topsort(graph);

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
	for (i = 0; i < G->size; i++) 	G->node[i] = nodes[i];	

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

void Topsort(Graph G) {
	Queue Q = MakeNewQueue(G->size);
	int i, j, V=0, W=0;
	int *Indegree = (int *)malloc(sizeof(int)* G->size);
	
	for (i = 0; i < G->size; i++) {
		Indegree[i] = 0;
	}

	for (i = 0; i < G->size; i++) {
		for (j = 0; j < G->size; j++) {
			if (G->matrix[i][j] == 1) Indegree[j]++;
		}
	}

	for (i = 0; i < G->size; i++) {
		if (Indegree[i] == 0) Enqueue(Q, G->node[i]);
	}
	while (!IsEmpty(Q)) {
		j = Dequeue(Q);
		for (i = 0; i<G->size; i++) {
			if (G->node[i] == j) {
				V = i;
			}
		}
		for (i = 0; i < G->size; i++) {
			
			if (G->matrix[V][i] == 1) {
				if (--Indegree[i] == 0) {
					Enqueue(Q, G->node[i]);
				}
			}
		}
	}
	for (i = 0; i < Q->max_queue_size; i++) {
		printf("%d ", Q->key[i]);
	}
	printf("\n");
}

Queue MakeNewQueue(int X) { 
	Queue Q = (Queue)malloc(sizeof(struct _Queue));
	Q->key = (int*)malloc(sizeof(int)*X);
	Q-> first=0;
	Q-> rear= -1;
	Q-> qsize = 0;
	Q-> max_queue_size = X;
	MakeEmpty(Q);
	return Q;
}

int IsEmpty(Queue Q) {
	return Q->first > Q->rear;
}

int IsFull(Queue Q) {
	return Q->max_queue_size - 1 == Q->rear;
}

int Dequeue(Queue Q) {
	if (IsEmpty(Q)) return 0;
	return Q->key[Q->first++];
}

void Enqueue(Queue Q, int X) {//a new element at the end of the element in the queue.
	if (IsFull(Q)) return;
	Q->key[++Q->rear] = X;
}

void DeleteQueue(Queue Q) {
	free(Q->key);
	free(Q);
}

void MakeEmpty(Queue Q) {
	int i = 0;
	for (i = 0; i < Q->max_queue_size; i++) Q->key[i] = 0;
}
