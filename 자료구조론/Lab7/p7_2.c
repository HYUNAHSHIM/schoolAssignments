#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x, y) {int temp=0; temp=x; x=y; y=temp;}

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
int DeleteMax(Heap* heap);
void PrintHeap(Heap* heap);

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
		case 'd':		
			DeleteMax(maxHeap);	
			break;		
		case 'p':		
			PrintHeap(maxHeap);	
			break;
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
		printf("Insertion Error : Max Heap is full.\n");     		
		return;	
	}	
	if(Find(H, value)){	
		printf("%d is already in the tree.\n",value);
		return;
	}
	H->Elements[++H->Size] = value;
	/*i = H->Elements[H->Size];
	while (i > 1) {
		if (H->Elements[i] > H->Elements[i / 2]) {
			SWAP(H->Elements[i], H->Elements[i / 2]);
			i /= 2;
		}
		else break;
	}*/
	int mPos = H->Size;
	int parPos = mPos/2;
	while(H->Elements[mPos]>H->Elements[parPos]){
		SWAP(H->Elements[mPos],H->Elements[parPos]);
		mPos=parPos;
		parPos=mPos/2;
	}
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

int DeleteMax(Heap* heap) {
	Heap *H = heap;
	int returnVal = H->Elements[0];

	if (H->Size == 0) {
		printf("Deletion Error : Max heap is empty!\n");
		return 0;
	}

	SWAP(H->Elements[1], H->Elements[H->Size]);
	H->Size--;

	int root = 1;
	int leftChild;
	int rightChild;
	
	while(root<=H->Size){
		leftChild = root * 2;
		rightChild = root * 2+1;

		if(leftChild > H->Size){
			break;
		}
		else if(rightChild > H->Size){
			if(H->Elements[leftChild]>H->Elements[root]){
				SWAP(H->Elements[leftChild], H->Elements[root]);
				root = leftChild;
			}
			else break;
		}
		else{
			if(H->Elements[leftChild] > H->Elements[root] && H->Elements[rightChild] > H->Elements[root]){
				if(H->Elements[leftChild] < H->Elements[rightChild]){
					SWAP(H->Elements[rightChild],H->Elements[root]);
					root = rightChild;
				}
				else{
					SWAP(H->Elements[leftChild],H->Elements[root]);
					root = leftChild;
				}
			}
			else if (H->Elements[leftChild] > H->Elements[root]){
				SWAP(H->Elements[leftChild],H->Elements[root]);
				root=leftChild;
			}
			else if(H->Elements[rightChild] > H->Elements[root]){
				SWAP(H->Elements[rightChild],H->Elements[root]);
				root = rightChild;
			}
			else break;
		}
	}
	return returnVal;

}

void PrintHeap(Heap* heap) {
	Heap *H = heap;
	int i=0;

	if (H->Size == 0) {
		printf("Print Error : Max heap is empty!\n");
		return;
	}

	for (i = 1; i < H->Size+1; i++) {
		printf("%d ", H->Elements[i]);
	}
	printf("\n");
}
