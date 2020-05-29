#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List; 
typedef PtrToNode Position; 
typedef int ElementType; 

struct Node { 
	ElementType element; 
	Position Next; 
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Delete(ElementType X, List L); 
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
void PrintList(List L);


int main(int argc, char *argv[]) {
	char command;
	int key1, key2;

	FILE *input;
	Position header = NULL;
	Position tmp = NULL;

	if (argc == 1) {
		input = fopen("input.txt", "r");
	}
	else {
		input = fopen(argv[1], "r");
	}

	header = MakeEmpty(header);

	while (1) {
		command = fgetc(input);
		if (feof(input)) break;

		switch (command) {

		case 'i':
			fscanf(input, "%d %d", &key1, &key2);
			
			tmp = Find(key1, header);
			if (tmp != NULL) {
				printf("There already is an element with key %d. Insertion failed\n", key1);
				break;
			}
			tmp = Find(key2, header);
			if (tmp == NULL){
				printf("Insertion(%d) Failed : cannot find the location to be inserted\n", key1);
				break;
			}
			Insert(key1, header, tmp);
			break;

		case 'd':
			fscanf(input, "%d", &key1);
			tmp = Find(key1, header);
			if (tmp == NULL){
				printf("Deletion failed : element %d is not in the list\n",key1);
				break;
			}
			Delete(key1, header);
			break;

		case 'f':
			fscanf(input, "%d", &key1);
			tmp = FindPrevious(key1, header);
			if (IsLast(tmp, header)) {
				printf("Could not find %d in the list\n", key1);
			}
			else {
				if (tmp->element > 0) {
					printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
				}
				else {
					printf("Key of the previous node of %d is header.\n", key1);
				}
			}
			break;

		case 'p':
			PrintList(header);
			break;
		default:
			break;
		}
	}
	
	DeleteList(header);
	fclose(input);
	return 0;
}

List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->element = 0;
	L->Next = NULL;
	return L;
}

int IsEmpty(List L) {
	return L->Next == NULL;
}

int IsLast(Position P, List L) {
	return P->Next == NULL;
}

void Insert(ElementType X, List L, Position P) {
	Position TmpCell;

	TmpCell = malloc(sizeof(struct Node));
	/*if (TmpCell == NULL) {
		printf("Out of space!!!");
	}*/
	TmpCell->element = X;
	TmpCell->Next = (IsLast(P, L)) ? NULL : P->Next;
	P->Next = TmpCell;
	
}

Position Find(ElementType X, List L) {
	Position P;

	if (X == -1) {
		return L;
	}
	
	P = L->Next;   
	while (P != NULL && P->element != X) {
		
		P = P->Next;
	}
	return P;
}

Position FindPrevious(ElementType X, List L) {
	Position P;
	P = L;    
	while (P->Next != NULL && P->Next->element != X) {
		P = P->Next;
	}
	return P;
}

void Delete(ElementType X, List L) {
	Position P, TmpCell;
	P = FindPrevious(X, L);
	if (!IsLast(P, L))
	{
		
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
	
		free(TmpCell);
	}
}

void DeleteList(List L) {
	Position P, Tmp;
	P = L->Next;  
	
	L->Next = NULL;   
	while (P != NULL) { 
		Tmp = P->Next;
		free(P);     
		P = Tmp;
	}
}

void PrintList(List L) {
	Position P;
	P = L->Next;
	while (P != NULL) {
		printf("key: %d\t", P->element);
		P = P->Next;
	}
	printf("\n");
}
