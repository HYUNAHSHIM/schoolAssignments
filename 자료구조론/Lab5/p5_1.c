#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int value;
	struct Tree* left;
	struct Tree* right;
}Tree;

Tree* insertNode(Tree *root, int key);
void printInorder(Tree *root);
void deleteTree(Tree *root);
Tree* find(int key, Tree* root);

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree* root = NULL;

	while (!feof(fi))
	{
		fscanf(fi, "%c", &cv);
		switch (cv)
		{
		case 'i':
			fscanf(fi, "%d", &key);

			if (find(key, root) != NULL)
				printf("Insertion Error : There is already %d in the tree.\n", key);
			else
				printf("insert %d\n", key);

			root = insertNode(root, key);

			break;

		case 'p':
			fscanf(fi, "%c", &cv);
			if (cv == 'i') printInorder(root);
			printf("\n");

			break;
		}
	}

	deleteTree(root);
}

Tree* insertNode(Tree* root, int key)
{
	if (root == NULL)
	{
		root = malloc(sizeof(struct Tree));
		root->value = key;
		root->left = root->right = NULL;
	}
	else if (key < root->value)
		root->left = insertNode(root->left, key);
	else if (key > root->value)
		root->right = insertNode(root->right, key);

	return root;
}

void printInorder(Tree* root)
{
	if (root == NULL) return;

	if (root->left != NULL) printInorder(root->left);
	printf("%d ", root->value);
	if (root->right != NULL) printInorder(root->right);
}

void deleteTree(Tree* root)
{
	if (root == NULL)
		return;

	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
}

Tree* find(int key, Tree* root)
{
	if (root == NULL)
		return NULL;

	if (key < root->value)
		return find(key, root->left);
	else if (key > root->value)
		return find(key, root->right);
	else
		return root;
}