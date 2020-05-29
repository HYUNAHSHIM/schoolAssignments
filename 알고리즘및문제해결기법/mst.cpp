//2017029898_½ÉÇö¾Æ_508

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Edge
{
	int u;
	int v;
	int w;
	int valid;
}Edge;

bool cmp(const Edge& e1, const Edge& e2)
{
	if (e1.w != e2.w) return e1.w < e2.w;
	if (e1.u != e2.u) return e1.u < e2.u;
	else return e1.v < e2.v;
}

vector<Edge> vec;
int d[1001], cnt;

int find(int v)
{
	int r = v;
	while (d[r] > 0)
	{
		r = d[r];
	}
	return r;
}

void union_vertex(int u, int v)
{
	if (d[u] < d[v]) d[v] = u;
	else
	{
		if (d[u] == d[v]) d[v]--;
		d[u] = v;
	}
}

int main()
{
	int n; cin >> n;

	int a, b, c;
	while (scanf("%d %d %d", &a, &b, &c) != EOF)
	{
		Edge e;
		if (a < b) e.u = a, e.v = b;
		else e.u = b, e.v = a;
		e.w = c; e.valid = 0;
		vec.push_back(e);
	}
	sort(vec.begin(), vec.end(), cmp);
	for (int i = 1; i <= n; ++i) d[i] = 0;
	for (int i = 0; i < vec.size(); ++i)
		if (find(vec[i].u) != find(vec[i].v))
		{
			union_vertex(find(vec[i].u), find(vec[i].v));
			cnt++; vec[i].valid = 1;
		}
	cout << cnt << endl;
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i].valid) printf("%d %d %d\n", vec[i].u, vec[i].v, vec[i].w);
	return 0;
}