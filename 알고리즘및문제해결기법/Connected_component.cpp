//2017029898_½ÉÇö¾Æ_508

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int visit[1001], cc[1001];
vector<int> vec[1001];

int cnt, n;

void dfs(int v)
{
	visit[v] = true; cc[v] = cnt;
	for (int i = 1; i <= n; ++i)
		if (find(vec[v].begin(), vec[v].end(), i) != vec[v].end() && !visit[i])
			dfs(i);
}

int main()
{
	int a, b; cin >> n;
	for (int i = 1; i <= n; ++i) visit[i] = 0;

	while (!cin.eof())
	{
		cin >> a >> b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}

	for (int i = 1; i <= n; ++i) if (!visit[i]) cnt++, dfs(i);

	cout << cnt << endl;
	for (int i = 1; i <= n; ++i) cout << cc[i] << endl;
	return 0;
}