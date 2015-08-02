#include <cstdio>
#include <cstring>
#include <vector>
#define MAX 905

using namespace std;

int vs, es;
vector<int> g[MAX];
int pre[MAX];
int f[MAX];
int vleft[MAX], top;
int lca[MAX][MAX];
int cnt[MAX];

inline int input()
{
	char c;
	for (c = getchar(); c < 48 || c > 57; c = getchar()) ;
	int x = c - 48;
	for (c = getchar(); c > 47 && c < 58; c = getchar())
		x = x * 10 + c - 48;
	return x;
}

int findF(int idx)
{
	if (f[idx] == idx) return idx;
	return f[idx] = findF(f[idx]);
}

void unionF(int idx1, int idx2)
{
	int f1 = findF(idx1), f2 = findF(idx2);
	f[idx2] = idx1;
}

void dfs(int idx)
{
	int i, sz = g[idx].size();
	for (i = 0; i < sz; i++)
	{
		int &idx2 = g[idx][i];
		dfs(idx2);
		vleft[++top] = idx2;
		unionF(idx, idx2);
	}
	for (i = 0; i <= top; i++)
		lca[ vleft[i] ][idx] =
		lca[idx][ vleft[i] ] = findF( vleft[i] );
}
			

int main()
{
	int i, j, vi, vj, ps;
	while (scanf(" %d", &vs) == 1)
	{
		top = -1;
		for (i = 1; i <= vs; i++)
		{
			g[i].clear();
			pre[i] = i;
			f[i] = i;
			cnt[i] = 0;
		}
			
		for (i = 0; i < vs; i++)
		{
			vi = input();
			es = input();
			while (es--)
			{
				vj = input();
				g[vi].push_back(vj);
				pre[vj] = vi;
			}
		}
		while (pre[vi] != vi)
			vi = pre[vi];
		
		dfs(vi);
		
		ps = input();
		while (ps--)
		{
			vi = input();
			vj = input();
			cnt[ lca[vi][vj] ]++;
		}
		
		for (i = 1; i <= vs; i++)
			if (cnt[i] > 0)
				printf("%d:%d\n", i, cnt[i]);
	}
	return 0;
}
