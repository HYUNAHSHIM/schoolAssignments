//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>
#define SWAP(x,y) {int p = x; x=y; y=p;}

void Max_heapify(int* arr, int n, int k) {

	int tmp = k;
	if (n < k * 2) return;//if there's no child node
	if (n == k * 2) {//if there's only left child node
		if (arr[k] < arr[k * 2]) {
			tmp = k * 2;
		}
	}
	else {
		if (arr[k * 2] > arr[k * 2 + 1]) {//change with left child node
			if (arr[k] < arr[k * 2]) {
				tmp = k * 2;
			}
		}
		else {//change with right child node
			if (arr[k] < arr[k * 2 + 1]) {
				tmp = k * 2 + 1;
			}
		}
	}
	if (tmp != k) {//change
		SWAP(arr[k], arr[tmp]);
		k = tmp;
		Max_heapify(arr, n, tmp);
	}
}

int main(void) {
	int c = 0, qsize = 0, n = 0, count = 0, i = 0, sn = 0, tn = 0;
	int *queue = new int[100000];

	while (true) {
		scanf("%d", &c);
		if (c == 0) {
			for (i = n; i >n - count; i--) {
				printf("%d ", queue[i]);
			}
			printf("\n");
			for (i = 1; i <= qsize; i++) {
				printf("%d ", queue[i]);
			}
			delete[] queue;
			return 0;
		}
		else if (c == 1) {
			scanf("%d", &sn);
			qsize++;
			n++;
			queue[qsize] = sn;
			for (i = qsize / 2; i >= 1; i--) {
				if (queue[i]< queue[i * 2] || queue[i]<queue[i * 2]) {
					Max_heapify(queue, qsize, i);
				}
			}
		}
		else if (c == 2) {
			SWAP(queue[qsize], queue[1]);
			qsize--;
			Max_heapify(queue, qsize, 1);
			count++;
		}
		else if (c == 3) {
			scanf("%d %d", &sn, &tn);
			queue[sn] = tn;
			for (i = sn; i >= 1; i--) {
				Max_heapify(queue, qsize, i);
			}
		}
		else {
			return 0;
		}
	}

	delete[] queue;
	return 0;
}