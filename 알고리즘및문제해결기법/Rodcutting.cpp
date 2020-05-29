//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>

void RodCut(int *p, int n) {
	int i = 0, j = 0, max=0;
	int *r = new int[n+1];
	int *s = new int[n+1];

	r[0] = 0;
	for (i = 1; i <= n; i++) {
		int q = -1;
		for (j = 1; j <= i; j++) {
			if (q < p[j] + r[i - j]) {
				q = p[j] + r[i - j];
				s[i] = j;
			}
		}
		r[i] = q;
	}
	
	for (i = 0; i <= n; i++) {
		if (r[i] >= max) {
			max = r[i];
		}
	}
	printf("%d\n", max);
	while (n > 0) {
		printf("%d ", s[n]);
		n = n - s[n];
	}

	delete[] r;
	delete[] s;
}

int main(void) {
	int n, i;
	scanf("%d", &n);

	int *p = new int[n+1];
	for (i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
	}

	RodCut(p, n);

	delete[] p;
	
	return 0;
}