//2017029898_½ÉÇö¾Æ_508
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int m, a, b;
vector<vector<int> > graph;
bool visited[32123];
vector<int> ans;
bool dag;

void dfs(int a)
{
	if (visited[a]) {
		return;
	}
	visited[a] = true;

	for (int i = 0; i<graph[a].size(); i++) {
		int b = graph[a][i];
		dfs(b);
	}

	ans.push_back(a);
}

int main()
{
	scanf("%d", &m);
	graph.resize(m + 1);
	dag = true;
	for (int i = 0; i<m; i++) {
		scanf("%d %d", &a, &b);
		graph[a].push_back(b);
	}

	for (int i = 1; i <= m; i++) {
		dfs(i);
	}

	reverse(ans.begin(), ans.end());

	if (dag == true) {
		printf("1\n");
		for (int i = 0; i < ans.size(); i++) {
			printf("%d ", ans[i]);
		}
	}
	else {
		printf("0");
	}


	return 0;
}
