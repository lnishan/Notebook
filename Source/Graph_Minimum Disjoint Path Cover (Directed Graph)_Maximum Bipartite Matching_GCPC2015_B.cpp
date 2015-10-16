/*
Max Bipartite Matching (call it MA)
Min Vertex Cover = MA
Max Independent Set = V - MA

Directed graph:
Minimum Disjoint Path Cover
    => Build a new graph, Edge (Vi, Vj) = Edge (Out(Vi), In(Vj))
    = V - MA(new graph)
Minimum Path Cover
    => Floyd Warshall to obtain transitive closure
    => Build a new graph, Vi can reach Vj  = Edge (Out(Vi), In(Vj))\
    = V - MA(new graph)
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int N = 1005;
const int NN = N + N;

vector<int> g[NN];
char vst[NN];
int match[NN];
int ma;

bool dfs(int vi)
{
	for (auto &vj: g[vi])
	{
		if (vst[vj]) continue;
		vst[vj] = 1;
		if (match[vj] == -1 || dfs(match[vj]))
		{
			match[vi] = vj;
			match[vj] = vi;
			return true;
		}
	}
	return false;
}

int main()
{
	int i, j, n, d;
	int vi, vj;
	scanf("%d", &n);
	ma = 0; // vst = 0
	fill(match, match + n * 2, -1);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &d);
		for (j = 0; j < d; j++)
		{
			scanf("%d", &vj);
			g[n + i].push_back(vj);
			g[vj].push_back(n + i);
		}
	}
	for (i = 0; i < n * 2; i++)
		if (match[i] == -1)
		{
			fill(vst, vst + n * 2, 0);
			ma += dfs(i);
		}
	printf("%d\n", n - ma);
	return 0;
}
