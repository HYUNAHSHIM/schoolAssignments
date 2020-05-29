#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
typedef struct AVLNode {
	ElementType Element;	
	AVLTree Left;
	AVLTree Right;
	int Height;
}AVLNode;

AVLTree Insert(ElementType X, AVLTree T);
void printInorder(AVLTree T);
void DeleteTree(AVLTree T);
int heightF(Position P);
int Max(int A, int B);
AVLNode* find(ElementType Element, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);

int main(int argc, char **argv) {	

	FILE *fp = fopen(argv[1], "r");
	AVLTree myTree = NULL;	
	int num;
	if (fp == NULL) {	
		printf("There is no file : %s\n", argv[1]);	
		exit(-1);
	}	
	while (fscanf(fp, "%d", &num) != EOF) {	
		if (find(num, myTree) != NULL) {	
			printf("[Error] %d already in the tree! \n", num);		
			printInorder(myTree);		
			printf("\n");	
		}	
		else{	
			myTree = Insert(num, myTree);	
			printInorder(myTree);	
			printf("\n");	
		}
	}
	DeleteTree(myTree);
	return 0;
}

AVLTree Insert(ElementType X, AVLTree T) {
	if (T == NULL) {	
		T = malloc(sizeof(struct AVLNode));	
		if (T == NULL) {	
			printf("Out of space!!!");	
			return T;	
		}		
		else {		
			T->Element = X;		
			T->Height = 0;		
			T->Left = T->Right = NULL;	
			return T;
		}

	}
	else if (X < T->Element) {	
		T->Left = Insert(X, T->Left);	
		if (heightF(T->Left) - heightF(T->Right) == 2) {	
			if (X < T->Left->Element) {	
				T = SingleRotateWithLeft(T);	
			}	
			else {	
				T = DoubleRotateWithLeft(T);	
			}	
		}
	}	
	else if (X > T->Element) {
		T->Right = Insert(X, T->Right);	
		if (heightF(T->Right) - heightF(T->Left) == 2) {	
			if (X > T->Right->Element) {	
				T = SingleRotateWithRight(T);
			}	
			else {	
				T = DoubleRotateWithRight(T);	
			}		
		}
	}
	T->Height = Max(heightF(T->Left), heightF(T->Right)) + 1;
	return T;
}

void printInorder(AVLTree T) {	
	if (T == NULL) return;	
	if (T->Left != NULL) {	
		printInorder(T->Left);
	}	
	printf("%d(%d) ", T->Element, T->Height);	
	if (T->Right != NULL) {	
		printInorder(T->Right);
	}
}

void DeleteTree(AVLTree T) {
	if (T == NULL)	return;
	DeleteTree(T->Left);	
	DeleteTree(T->Right);
	free(T);
}

int heightF(Position P) {	
	if (P == NULL) {			
		return -1;
	}	
	else {	
		return P->Height;	
	}
}

int Max(int A, int B) {
	if (A > B) {
		return A;
	}	
	else return B;
}

AVLNode* find(ElementType key, AVLTree T) {
	if (T == NULL)	return NULL;
	if (key < T->Element)	return find(key, T->Left);
	else if (key > T->Element)	return find(key, T->Right);	
	else return T;
}

Position SingleRotateWithLeft(Position node) {
	Position tmp;
	tmp = node->Left;  
	node->Left = tmp->Right;             
	tmp->Right = node;
	node->Height = Max(heightF(node->Left), heightF(node->Right)) + 1;  
	tmp->Height = Max(heightF(tmp->Left), node->Height) + 1;
	return tmp;
}

Position SingleRotateWithRight(Position node) {
	Position tmp;
	tmp = node->Right;  
	node->Right = tmp->Left;
	tmp->Left = node;
	node->Height = Max(heightF(node->Left), heightF(node->Right)) + 1;
	tmp->Height = Max(heightF(tmp->Right), node->Height) + 1;
	return tmp;
}

Position DoubleRotateWithLeft(Position node) {
	node->Left = SingleRotateWithRight(node->Left); 
	return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
	node->Right = SingleRotateWithLeft(node->Right);
	return SingleRotateWithRight(node);
}
