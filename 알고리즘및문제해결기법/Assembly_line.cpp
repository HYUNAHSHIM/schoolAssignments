//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

int main(void) {
	int n, e1, e2, x1, x2, i=0;
	scanf("%d", &n);
	scanf("%d %d", &e1, &e2);
	scanf("%d %d", &x1, &x2);

	int *a1 = new int[n];
	int *a2 = new int[n];

	int *t1 = new int[n - 1];
	int *t2 = new int[n - 1];

	int **L = NULL;
	int tmp[2][2];
	int *result = new int[n];

	L = new int*[2];
	for (i = 0; i < 2; i++) {
		L[i] = new int[n];
	}
	for (i = 0; i < n; i++) {
		scanf("%d", &a1[i]);
	}
	for (i = 0; i < n; i++) {
		scanf("%d", &a2[i]);
	}
	for (i = 0; i < n - 1; i++) {
		scanf("%d", &t1[i]);
	}
	for (i = 0; i < n - 1; i++) {
		scanf("%d", &t2[i]);
	}

	tmp[0][0] = e1 + a1[0];
	tmp[1][0] = e2 + a2[0];

	for (i = 1; i < n; i++) {
		if ((tmp[0][0] + a1[i]) <= tmp[1][0] + t2[i - 1] + a1[i]) {
			tmp[0][1] = tmp[0][0] + a1[i];
			L[0][i] = 1;
		}
		else {
			tmp[0][1] = tmp[1][0] + t2[i - 1] + a1[i];
			L[0][i] = 2;
		}

		if ((tmp[0][0] + t1[i - 1] + a2[i]) <= tmp[1][0] + a2[i]) {
			tmp[1][1] = tmp[0][0] + t1[i - 1] + a2[i];
			L[1][i] = 1;
		}
		else {
			tmp[1][1] = tmp[1][0] + a2[i];
			L[1][i] = 2;
		}

		tmp[0][0] = tmp[0][1];
		tmp[1][0] = tmp[1][1];
	}


	if (tmp[0][0] + x1 <= tmp[1][0] + x2) {
		printf("%d\n", tmp[0][0] + x1);
		result[0] = 1;
	}
	else {
		printf("%d\n", tmp[1][0] + x2);
		result[0] = 2;
	}

	for (i = n - 1; i > 0; i--) {
		result[n-i] = L[result[n - i - 1]-1][i];
	}

	for (i = 0; i < n; i++) {
		printf("%d %d\n", result[n-i-1], i+1);
	}

	delete[] a1;
	delete[] a2;
	delete[] t1;
	delete[] t2;
	delete[] result;
	for (i = 0; i < 2; i++) {
		delete[] L[i];
	}
	delete[] L;
}