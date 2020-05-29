#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
	int* key;	
	int top; 
	int max_stack_size; 
}Stack;

Stack* CreateStack(int max);
void Push(Stack* S, int X); 
int IsFull(Stack *S);
int IsEmpty(Stack *S);
int Pop(Stack* S);
void DeleteStack(Stack* S);

int main(int argc, char* argv[]) {
	FILE* fi = fopen(argv[1], "r");
	Stack* stack;	
	char input_str[101];
	int max, i = 0, a, b, result;
	fgets(input_str, 101, fi);
	max = strlen(input_str);
	stack = CreateStack(max);	
	printf("Top numbers :");
	
	while (input_str[i] != '#') {

		switch (input_str[i]) {
		case '0': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8': case'9':
			Push(stack, input_str[i] - 48);
			printf("%d ", Pop(stack));
			i++;
			break;
		
		case '+': 
			stack->key[stack->top-1] = stack->key[stack->top-1] + stack->key[stack->top];
			stack->top--;
			printf("%d ", Pop(stack));
			i++;
			break;
		
		case '-':
			stack->key[stack->top - 1] = stack->key[stack->top - 1] - stack->key[stack->top];
			stack->top--;
			printf("%d ", Pop(stack));
			i++;
			break;

		case '/':
			stack->key[stack->top - 1] = stack->key[stack->top - 1] / stack->key[stack->top];
			stack->top--;
			printf("%d ", Pop(stack));
			i++;
			break;

		case '%':
			stack->key[stack->top - 1] = stack->key[stack->top - 1] % stack->key[stack->top];
			stack->top--;
			printf("%d ", Pop(stack));
			i++;
			break;

		case '*':
			stack->key[stack->top - 1] = stack->key[stack->top - 1] * stack->key[stack->top];
			stack->top--;
			printf("%d ", Pop(stack));
			i++;
			break;

		default:
			printf("Wrong input: error");
			break;

		}
			
	}

	result = stack->key[stack->top];
	printf("\nevaluation result : %d\n", result);
	fclose(fi);
	DeleteStack(stack);
}

Stack* CreateStack(int max) {	
	Stack* S = NULL;	
	S = (Stack*)malloc(sizeof(max));	
	S->key = (int*)malloc(sizeof(int)*max);
	S->max_stack_size = max;	
	S->top = -1;	
	return S;
}

void Push(Stack* S, int X) {
	if (IsFull(S)) {	
		printf("Full stack");
	}	
	else {	
		S->key[++S->top] = X;
	}
}

int IsFull(Stack *S) {
	if (S->top == S->max_stack_size-1) {	
		return 1;
	}	
	else {
		return 0;
	}
}

int IsEmpty(Stack *S) {	
	if (S->top == -1) {	
		return 1;	
	}	
	else {	
		return 0;
	}
}

int Pop(Stack* S) {	
	if (IsEmpty(S)) {	
		printf("Empty stack");
		return 0;	
	}
	else {	
		//S->top--;
		return S->key[S->top];
			}
}

void DeleteStack(Stack* S) {
	free(S->key);
	free(S);
}
