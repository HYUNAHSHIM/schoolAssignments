//2017029898_½ÉÇö¾Æ_508

#include <stdio.h>

int main(void) {

	int n = 0, i = 0, j = 0;
	scanf("%d", &n);

	int * arr = new int[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (j = 1; j < n; j++) {
		int key = arr[j];
		i = j - 1;
		while (i >= 0 && arr[i] < key) {
			arr[i + 1] = arr[i];
			i = i - 1;
		}
		arr[i + 1] = key;
	}

	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}

	delete[] arr;
	return 0;
}
