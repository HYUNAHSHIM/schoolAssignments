//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

void merge(int *arr, int *tmp, int L, int R, int RE) {
	int i, LE, n, TmpPos;
	LE = R-1 ;
	TmpPos = L;
	n = RE - L + 1;

	while (L <= LE && R <= RE) {
		if (arr[L] >= arr[R])
			tmp[TmpPos++] = arr[L++];
		else
			tmp[TmpPos++] = arr[R++];
	}

	while (L <= LE)
		tmp[TmpPos++] = arr[L++];
	while (R <= RE)
		tmp[TmpPos++] = arr[R++];
	for (i = 0; i < n; i++, RE--)
		arr[RE] = tmp[RE];

}

void merge_sort(int *arr, int *tmp, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		merge_sort(arr, tmp,p, q);
		merge_sort(arr,tmp, q + 1, r);
		merge(arr,tmp, p, q+1, r);
	}
}

int main(void) {

	int n = 0, i = 0, j = 0;
	scanf("%d", &n);

	int *tmp = new int[n];
	int * arr = new int[n];
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	merge_sort(arr, tmp, 0, n - 1);

	for (i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}

	delete[] arr;
	delete[] tmp;
	return 0;
}