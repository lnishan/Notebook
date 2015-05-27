#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX_V = 2002;

int vs, es;
vector<int> g[MAX_V];
int t, low[MAX_V], dfn[MAX_V];
char instk[MAX_V];
int stk[MAX_V], top;
int scc_cnt;

void dfs(int vi)
{
	dfn[vi] = t++;
	low[vi] = dfn[vi];
	stk[++top] = vi;
	instk[vi] = 1;
	int i, sz = g[vi].size();
	for (i = 0; i < sz; i++)
	{
		int &vj = g[vi][i];
		if (dfn[vj] == -1)
		{
			dfs(vj);
			low[vi] = min(low[vi], low[vj]);
		}
		else if (instk[vj])
			low[vi] = min(low[vi], dfn[vj]);
	}
	if (low[vi] == dfn[vi])
	{
		scc_cnt++;
		while (stk[top] != vi)
		{
			instk[stk[top]] = 0;
			--top;
		}
		instk[stk[top]] = 0;
		--top;
	}
}

int main()
{
	int i, j;
	int v1, v2, dir;
	while (scanf("%d%d", &vs, &es) == 2 && (vs | es))
	{
		for (i = 1; i <= vs; i++) g[i].clear();
		t = 0;
		memset(dfn, -1, sizeof(dfn));
		memset(instk, 0, sizeof(instk));
		top = -1;
		scc_cnt = 0;
		for (i = 0; i < es; i++)
		{
			scanf("%d%d%d", &v1, &v2, &dir);
			g[v1].push_back(v2);
			if (dir == 2) g[v2].push_back(v1);
		}
		for (i = 1; i <= vs; i++)
			if (dfn[i] == -1)
				dfs(i);
		printf("%d\n", scc_cnt == 1);
	}
	return 0;
}	
