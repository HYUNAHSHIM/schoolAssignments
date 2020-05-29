//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>
#define SWAP(x,y) {int p=x; x=y; y=p;}

void Max_heapify(int* arr, int n, int k) {
	int tmp = k;
	if (n < k * 2) return;
	if (n == k * 2) {
		if (arr[k] < arr[k * 2]) {
			tmp = k * 2;
		}
	}
	else {
		if (arr[k * 2] > arr[k * 2 + 1]) {
			if (arr[k] < arr[k * 2]) {
				tmp = k * 2;
			}
		}
		else {
			if (arr[k] < arr[k * 2 + 1]) {
				tmp = k * 2 + 1;
			}
		}
	}
	if (tmp != k) {
		SWAP(arr[k], arr[tmp]);
		Max_heapify(arr, n,tmp);
	}
}

int main(void) {
	int n = 0, k = 0, i=0, heapsize=0;
	
	if (scanf("%d %d", &n, &k) <= 0) {
		return 0;
	}
	if (n < k) {
		return 0;
	}
	int *arr = new int[n+1];
	for (i = 1; i <= n; i++) {
		if (scanf("%d", &arr[i]) <= 0) {
			return 0;
		}
	}

	for (i = n / 2; i >= 1; i--) {
		Max_heapify(arr, n, i);
	}

	heapsize = n;
	for (i = n; i > n-k; i--) {
		SWAP(arr[i], arr[1]);
		heapsize = heapsize - 1;
		Max_heapify(arr,heapsize, 1);
	}

	for (i = n; i > n-k; i--) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	for (i = 1; i <=n-k; i++) {
		printf("%d ", arr[i]);
	}

	delete[] arr;
	return 0;
}