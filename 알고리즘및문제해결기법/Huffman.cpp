//2017029898_½ÉÇö¾Æ_508

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define CharNum 30000

static int sum = 0;

typedef struct HeapNode {
	char *ch;
	int freq;
	struct HeapNode *left, *right;
}HeapNode;

typedef struct {
	int heapSize;
	HeapNode *heap[CharNum];
}MinHeap;

void Insert(HeapNode *element, MinHeap *h) {

	h->heapSize++;
	h->heap[h->heapSize] = element;
	int cur = h->heapSize;
	while (h->heap[cur / 2]->freq > element->freq) {
		h->heap[cur] = h->heap[cur / 2];
		cur = cur / 2;
	}
	h->heap[cur] = element;
}
HeapNode *DeleteMin(MinHeap *h) {
	HeapNode * minElement, *lastElement;
	int child, cur;
	minElement = h->heap[1];
	lastElement = h->heap[h->heapSize--];
	for (cur = 1; 2 * cur <= h->heapSize; cur = child) {
		child = cur * 2;
		if (child != h->heapSize && h->heap[child + 1]->freq < h->heap[child]->freq) child++;
		if (lastElement->freq > h->heap[child]->freq) h->heap[cur] = h->heap[child];
		else break;
	}
	h->heap[cur] = lastElement;
	return minElement;
}
void count(HeapNode *tmp, int cnt) {

	cnt++;
	if (tmp->left == NULL && tmp->right == NULL) {
		sum = sum + (tmp->freq)*cnt;
		return;
	}
	count(tmp->left, cnt);
	count(tmp->right, cnt);
}

int main() {
	int n, s, bit = 1, cnt = -1;
	MinHeap h;
	h.heap[0] = (HeapNode*)malloc(sizeof(HeapNode));
	h.heap[0]->freq = 0;
	h.heapSize = 0;//initialize

	scanf("%d", &n);
	char *ch = (char*)malloc(sizeof(char)*n);
	int freq, i;

	for (i = 0; i < n; i++) {
		scanf("%s %d", &ch[i], &freq);
		HeapNode * tmp = (HeapNode*)malloc(sizeof(HeapNode));
		tmp->ch = &ch[i];
		tmp->freq = freq;
		tmp->left = tmp->right = NULL;
		Insert(tmp, &h);
	}//minheapify
	scanf("%d", &s);
	for (i = 0; i < n - 1; i++) {
		HeapNode *left = DeleteMin(&h);
		HeapNode *right = DeleteMin(&h);
		HeapNode *tmp = (HeapNode*)malloc(sizeof(HeapNode));
		tmp->ch = 0;
		tmp->left = left;
		tmp->right = right;
		tmp->freq = left->freq + right->freq;
		Insert(tmp, &h);
	}

	HeapNode *tree = DeleteMin(&h);

	count(tree, cnt);

	i = 1;
	while (true) {
		if (n < 2 * i && n >= i) {
			break;
		}
		i *= 2;
		bit++;
	}

	printf("%d\n", bit*s);
	printf("%d\n", sum);

	return 0;
}