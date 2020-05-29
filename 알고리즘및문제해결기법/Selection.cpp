//#2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

int main(void) {
	int n=0, m=0, i = 0, min=0, j=0, temp=0;
	
	if (scanf("%d %d", &n, &m) <= 0) {
		printf("you did not enter right number\n");
	}
	int *arr = new int[n];

	for (i = 0; i < n; i++) {
		if (scanf("%d", &arr[i]) <= 0) {
			printf("you did not enter right number\n");
		}
	}

	for (i = 0; i < m; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) min = j;
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	
	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}

	delete[] arr;
	return 0;
}