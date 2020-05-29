#include <stdio.h>
#include <stdlib.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Insert(ElementType X, List L, Position P);
void PrintList(List L);
List Find(ElementType x, List L);
void DeleteList(List L);

int main(int argc, char* argv[])
{
	char command;
	int key1, key2;
	FILE *input;
	Position header = NULL;
	Position tmp = NULL;

	if(argc == 1)
		input = fopen("input.txt", "r");
	else
		input = fopen(argv[1], "r");

	header = MakeEmpty(header);

	while(1)
	{
		command = fgetc(input);
		if(feof(input)) break;

		switch(command)
		{
			case 'i':
				fscanf(input, "%d %d", &key1, &key2);
				tmp = Find(key1, header);
				
				if(tmp!= NULL){
					printf("There already is an element with key %d. Insertion Failed\n", key1);
					break;
				}
				tmp=Find(key2, header);

				if(tmp == NULL){
					printf("Insertion %d Failed :cannnot find the location to be inserted.\n", key1);
					break;
				}

				Insert(key1, header, tmp);
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

List MakeEmpty(List L)
{
	L = (List)malloc(sizeof(struct Node));
	L->element = 0;
	L->next = NULL;
	return L;
}

int IsEmpty(List L)
{
	return L->next == NULL;
}

int IsLast(Position P, List L)
{
	return P->next == NULL;
}

void Insert(ElementType X, List L, Position P)
{
	Position temp;
	temp = malloc(sizeof(struct Node));
	temp->element = X;
	temp->next = (IsLast(P, L)) ? NULL : P->next;
	P->next = temp;
}

void PrintList(List L)
{
	Position p;
	p = L->next;

	while(p != NULL)
	{
		printf("key:%d\t", p->element);
		p = p->next;
	}
	printf("\n");
}

List Find(ElementType x, List L)
{
	Position p;

	if(x == -1)
		return L;

	p = L->next;
	while(p != NULL && p->element != x)
	{
		p = p->next;
	}

	return p;
}

void DeleteList(List L)
{
	Position p, temp;
	p = L->next;
	L->next = NULL;

	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}
