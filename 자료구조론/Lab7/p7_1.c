#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct HeapStruct {
	int Capacity;
	int Size;
	ElementType *Elements; 
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int IsFull(Heap *heap);
/*int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);*/

void main(int argc, char* argv[]) {
	FILE *fi = fopen(argv[1], "r");
	char cv;
	Heap* maxHeap;
	int heapSize, key;
	while (!feof(fi)) {
		fscanf(fi, "%c", &cv);
		switch (cv) {
		case 'n':
			fscanf(fi, "%d", &heapSize);
			maxHeap = CreateHeap(heapSize);
			break;
		case 'i':
			fscanf(fi, "%d", &key);
			Insert(maxHeap, key);
			break;
		/*case 'd':
			DeleteMax(maxHeap);
			break;
		case 'p':
			PrintHeap(maxHeap);
			break;*/
		case 'f':
			fscanf(fi, "%d", &key);
			if (Find(maxHeap, key)) {
				printf("%d is in the tree.\n", key);
			}
			else {
				printf("%d is not in the tree.\n", key);
			}
			break;
		}
	}
}

Heap* CreateHeap(int heapSize) {
	Heap *H;
	H = malloc(sizeof(struct HeapStruct));
	H->Elements = malloc(sizeof(int)*heapSize);
	H->Size = 0;
	H->Capacity = heapSize;
	memset(H->Elements, -987654321, sizeof(int)*heapSize);
	return H;
}

void Insert(Heap *heap, int value) {
	int i; 
	Heap *H = heap;
	if (IsFull(H)) {
		printf("Priority queue is full\n");     
		return;
	}
	if(Find(H, value)){
		printf("%d is already in the tree.\n",value);
		return;
	}
	for (i = ++H->Size; H->Elements[i / 2] < value; i /= 2) {
		H->Elements[i] = H->Elements[i / 2];
	} 
	H->Elements[i] = value;
	printf("insert %d\n", value);
}

int Find(Heap *heap, int value) {
	int i;
	Heap *H = heap;
	for (i = 1; i <= H->Size; i++) {
		if (H->Elements[i] == value) {
			return 1;
		}
	}
	return 0;
}

int IsFull(Heap *heap) {
	if (heap->Capacity == heap->Size) {
		return 1;
	}
	else {
		return 0;
	}
}
