//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

void PrintMatrix(int **s, int **m, int start, int end) {
	int i = 0, j=0;
	int a = s[start][end];
	if (a - start > 1) {
		printf("( ");
		PrintMatrix(s, m, start, a);
	}
	else {
		printf("( ");
		for (j = start; j <= a; j++) {
			printf("%d ", j);
		}
		if (a - start != 0) {
			printf(") ");
		}
	}
	if (end - (a + 1) > 1) {
		printf("( ");
		PrintMatrix(s, m, a + 1, end);
	}
	else {
		if (end-(a+1) != 0) {
			printf("( ");
		}
		for (j = a + 1; j <= end; j++) {
			printf("%d ", j);
		}
		printf(") ) ");
	}
	
}

void Matrixchain(int **s, int **m, int *p, int n) {
	int i = 0, j=0, l=0, k=0, q=0;

	for (i = 1; i < n+1; i++) {
		m[i][i] = 0;
	}
	for (l = 2; l < n+1; l++) {
		for (i = 1; i < n - l + 2; i++) {
			j = i + l - 1;
			m[i][j] = 2147483647;
			for (k = i; k < j; k++) {
				q = m[i][k] + m[k + 1][j] + p[i - 1]*p[k]*p[j];
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	
	printf("%d\n", m[1][n]);
	PrintMatrix(s, m, 1, n);

}

int main(void) {
	int n = 0, i=0;
	scanf("%d", &n);

	int *p = new int[n+1];
	for (i = 0; i < n+1 ; i++) {
		scanf("%d", &p[i]);
	}

	int **s = new int*[n+1];
	for (i = 0; i < n+1; i++) {
		s[i] = new int[n+1];
	}

	int **m = new int*[n+1];
	for (i = 0; i < n+1; i++) {
		m[i] = new int[n+1];
	}

	Matrixchain(s, m, p, n);
	
	delete[] p;
	for (i = 0; i < n+1; i++) {
		delete[] s[i];
		delete[] m[i];
	}
	delete[] s;
	delete[] m;

	return 0;
}