#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define MAX_V 102
#define INF 1 << 30

using namespace std;

struct edge{ int to, res, rev; };
vector<edge> g[MAX_V];
int lvl[MAX_V];
int iter[MAX_V];

void addEdge(int from, int to, int fcap, int bcap)
{
	g[from].push_back( edge{ to, fcap, g[to].size() } );
	g[to].push_back( edge{ from, bcap, g[from].size()-1 } );
}

void doFlow(edge &e, int f)
{
	e.res -= f;
	g[e.to][e.rev].res += f;
}

int bfs(const int &src, const int &sink)
{
	int qi;
	queue<int> q;
	memset(lvl, -1, sizeof(lvl));
	lvl[src] = 0;
	q.push(src);
	while (!q.empty())
	{
		qi = q.front(); q.pop();
		for (auto &e: g[qi])
			if (e.res > 0 && lvl[e.to] < 0)
			{
				lvl[e.to] = lvl[qi] + 1;
				q.push(e.to);
			}
	}
	return lvl[sink];
}

int dfs(int idx, int minF, const int &dest)
{
	if (idx == dest) return minF;
	int sz = g[idx].size(), ret;
	for (int &i = iter[idx]; i < sz; i++)
	{
		edge &e = g[idx][i];
		if (e.res > 0 && lvl[idx] < lvl[e.to])
		{
			ret = dfs(e.to, min(minF, e.res), dest);
			if (ret > 0)
			{
				doFlow(e, ret);
				return ret;
			}
		}
	}
	return 0;
}

int maxFlow(const int &src, const int &sink)
{
	int ret, f = 0;
	while ( bfs(src, sink) >= 0 )
	{
		memset(iter, 0, sizeof(iter));
		while ( (ret = dfs(src, INF, sink)) > 0)
			f += ret;
	}
	return f;
}

int main()
{
	int i, cases = 0, vs, src, sink, es, v1, v2, cap;
	while (scanf("%d", &vs) == 1 && vs > 0)
	{
		for (i = 1; i <= vs; i++) g[i].clear();
		scanf("%d%d%d", &src, &sink, &es);
		while (es--)
		{
			scanf("%d%d%d", &v1, &v2, &cap);
			addEdge(v1, v2, cap, cap);
		}
		printf("Network %d\n", ++cases);
		printf("The bandwidth is %d.\n\n", maxFlow(src, sink));
	}
	return 0;
}
