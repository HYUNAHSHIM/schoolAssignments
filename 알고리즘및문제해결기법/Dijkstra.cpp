//2017029898_½ÉÇö¾Æ_508
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#define INT_MAX 2147483647;

using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > pq;
vector<pair<int, int> > nod[5001];

int Dijk(int start, int v){
	int i, j, tmp;
	int* len = new int[v + 1];
	len[1] = 0;
	pq.push(make_pair(1, len[1]));
	for (i = 2; i <= v; i++) {
		len[i] = INT_MAX;
	}

	while (pq.empty() == false) {
		int from = pq.top().first;
		int tlen = pq.top().second;
		pq.pop();

		for (j = 0; j < nod[from].size(); j++) {
			int to = nod[from][j].first;
			if (len[from] == 2147483647) {
				tmp = nod[from][j].second;
			}
			else {
				tmp = nod[from][j].second + len[from];
			}
			if (tmp < len[to]){
				len[to] = tmp;
				pq.push(make_pair(to, len[to]));
			}
		}
	}

	int Max = len[1];
	for (int i = 2; i <= v; i++) {
		if (len[i] > Max) Max = len[i];
	}
	delete[] len;
	return Max;
}

int main(){
	int v, i, j, result;
	scanf("%d", &v);

	for (i = 1; i <= v; i++){
		int index, out;
		scanf("%d %d", &index, &out);
		for (j = 0; j < out; j++){
			int t, w;
			scanf("%d %d", &t, &w);
			nod[i].push_back(make_pair(t, w));
		}
	}

	result = Dijk(1, v);
	printf("%d", result);
	return 0;
}
