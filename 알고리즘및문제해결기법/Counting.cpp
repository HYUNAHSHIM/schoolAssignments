//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

int main(void) {
	int n, m, k, j=0, i=0, key=0, count=0;
	scanf("%d %d %d", &n, &m, &k);

	int *arr = new int[n+1];
	int *A = new int[k];
	int *B = new int[k];
	int *C = new int[m+1];//count

	for (i = 0; i < k; i++) {//initialize range
		scanf("%d %d", &A[i], &B[i]);
	}
	for (i = 1; i < n+1; i++) {//initialize arr
		arr[i] = 0;
	}
	for (i = 1; i < n+1; i++) {//insert key value to arr
		scanf("%d", &key);
		arr[i] = key;
	}
	for (i = 0; i < m+1; i++) {//initialize counting arr
		C[i] = 0;
	}
	for (i = 1; i < n + 1; i++) {//insert value to arr
		C[arr[i]]++;
	}

	for (i = 1; i < m + 1; i++) {
		C[i] += C[i - 1];
	}
	for (i = 0; i < k; i++) {
		printf("%d\n",C[B[i]] - C[A[i] - 1]);
	}
	
	delete[] arr;
	delete[] A;
	delete[] B;
	delete[] C;
	return 0;
}