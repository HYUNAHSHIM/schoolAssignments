//2017029898_½ÉÇö¾Æ_508

#include <stdio.h>

int main(void) {
	int a = 0;
	int b = 0;
	int i = 0, j = 0;
	int num = 0;

	scanf("%d %d", &a, &b);
	int c = 100000;

	int* A = new int[a];
	int* B = new int[b];
	int* C = new int[c];

	for (i = 0; i < a; i++) {
		scanf("%d", &A[i]);
	}
	for (i = 0; i < b; i++) {
		scanf("%d", &B[i]);
	}
	for (i = 0; i < c; i++) {
		C[i] = 0;
	}

	for (i = 0; i < a; i++) {
		C[A[i]]++;
	}
	for (i = 0; i < b; i++) {
		C[B[i]]++;
	}

	for (i = 0; i < c; i++) {
		if (C[i] == 2) {
			num++;
		}
	}

	printf("%d", num);
	return 0;

}