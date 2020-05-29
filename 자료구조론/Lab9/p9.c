#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _DisjointSet {
	int size_maze;
	int *ptr_arr;
} DisjointSets;

void init(DisjointSets *sets, DisjointSets *maze_print, int num);
void uni(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *sets, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);

int main(int argc, char*argv[]) {
	int num, i;
	FILE *fi = fopen(argv[1], "r");

	DisjointSets *sets, *maze_print;
	fscanf(fi, "%d", &num);
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));//means the number between the walls 
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));// means the wall -1:yes,0:no
	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	freeMaze(sets, maze_print);

	fclose(fi);
	return 0;
}

void init(DisjointSets *sets, DisjointSets *maze_print, int num) {
	sets->size_maze = num * num;
	for (int i = 1; i < sets->size_maze + 1; i++) {
		sets->ptr_arr[i] = 0;
	} //initialize sets, start with 1

	maze_print->size_maze = (num * 2 + 1) ^ 2;
	for (int i = 0; i < maze_print->size_maze; i++) {
		if (i % 2 == 0) {
			maze_print->ptr_arr[i] = 0;
		}
		else maze_print->ptr_arr[i] = -1;
	} //initialize maze_print

}

void uni(DisjointSets *sets, int i, int j) {
	int n = sets->ptr_arr[j];
	if (find(sets, i) == find(sets, j)) return;
	else {
		for (int k = 1; k <= sets->size_maze; k++) {
			if (sets->ptr_arr[k] == n) {
				sets->ptr_arr[k] = sets->ptr_arr[i];
			}
		}
	}
}

int find(DisjointSets *sets, int i) {
	return sets->ptr_arr[i];
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {
	srand((unsigned int)time(NULL));
	

}

void printMaze(DisjointSets *sets, int num) {
	for (int i = 0; i < sets->size_maze; i++) {
		if ((i + 1) % 7 == 0){
			printf("\n");
		}
		printf("%d", sets->ptr_arr[i]);
	}
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print) {
	free(sets);
	free(maze_print);
}
