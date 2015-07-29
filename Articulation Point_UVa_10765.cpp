#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

const int MAX_V = 10002;

pair<int, int> ans[MAX_V];
vector<int> g[10002];
int vs, es, t;
int low[MAX_V], dfn[MAX_V];

bool cmp(pair<int, int> a, pair<int, int> b)
{
	if (a.second != b.second)
		return a.second > b.second;
	else
		return a.first < b.first;
}

int dfs(int p, int vi)
{
	dfn[vi] = ++t;
	low[vi] = dfn[vi];
	int i, ch = 0, cnt = 0, sz = g[vi].size();
	for (i = 0; i < sz; i++)
	{
		int &vj = g[vi][i];
		if (dfn[vj] == -1)
		{
			++ch;
			dfs(vi, vj);
			if (low[vj] >= dfn[vi]) cnt++;
			low[vi] = min(low[vi], low[vj]);
		}
		else if (vj != p)
			low[vi] = min(low[vi], dfn[vj]);
	}
	if (p != -1) // not root
	{
		if (cnt) ans[vi].second = cnt+1;
	}
	else
	{
		if (ch > 1) ans[vi].second = ch;
	}
	return low[vi];
}

int main()
{
	int i, j, m, v1, v2;
	while (scanf("%d%d", &vs, &m) == 2 && (vs | m))
	{
		t = 0;
		memset(dfn, -1, sizeof(dfn));
		for (i = 0; i < vs; i++)
		{
			g[i].clear();
			ans[i].first = i;
			ans[i].second = 1;
		}
		while (scanf("%d%d", &v1, &v2) == 2 && !(v1 == -1 && v2 == -1))
		{
			g[v1].push_back(v2);
			g[v2].push_back(v1);
		}
		for (i = 0; i < vs; i++)
			if (dfn[i] == -1)
				dfs(-1, i);
		sort(ans, ans+vs, cmp);
		for (i = 0; i < m; i++)
			printf("%d %d\n", ans[i].first, ans[i].second);
		puts("");
	}
	return 0;
}
