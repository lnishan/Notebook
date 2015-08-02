#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100005;
const int lgN = 25;

int rmq[N << 1][lgN];
void build_rmq(int a[], int len)
{
	int i, j, i1, i2;
	for (i = 0; i < len; i++)
	{
		rmq[i][0] = i;
		for (j = 1; i - (1 << j) + 1 >= 0; j++)
		{
			i1 = rmq[i][j - 1];
			i2 = rmq[i - (1 << (j - 1))][j - 1];
			rmq[i][j] = a[i1] < a[i2] ? i1 : i2;
		}
	}
}
int get_rmq(int a[], int i, int j)
{
	if (i > j) swap(i, j);
	int i1, i2;
	int k, l = j - i + 1;
	for (k = 0; (1 << k) <= l; k++) ; --k;
	i1 = rmq[i + (1 << k) - 1][k];
	i2 = rmq[j][k];
	return a[i1] < a[i2] ? i1 : i2;
}

vector<int> g[N]; // 0-based
int t;
int dfn[N], lst[N << 1], dep[N << 1]; // o[i]: the i'th vertex visited, dfn[i]: the visited time of vertex i, dth[i]: the depth of vertex i
void dfs(int d, int vi)
{
	dfn[vi] = t;
	lst[t] = vi;
	dep[t] = d;
	t++;
	for (auto &vj: g[vi])
		if (dfn[vj] == -1) // not needed if directed tree
		{
			dfs(d + 1, vj);
			lst[t] = vi;
			dep[t] = d;
			t++;
		}
}
void build_lca(int n)
{
	fill(dfn, dfn + n, -1);
	t = 0;
	dfs(0, 0); // second paramter = root
	build_rmq(dep, t);
}
int get_lca(int vi, int vj)
{
	return lst[get_rmq(dep, dfn[vi], dfn[vj])];
}

// vector<int> g[N];
char vst[N];
int anc[N][lgN];
void dfs2(int d, int va, int vi)
{
	int i;
	vst[vi] = 1; // not needed if directed tree
	anc[vi][0] = va;
	for (i = 1; d - (1 << i) >= 0; i++)
		anc[vi][i] = anc[ anc[vi][i - 1] ][i - 1];
	for (auto &vj: g[vi])
		if (!vst[vj]) // not needed if directed tree
			dfs2(d + 1, vi, vj);
}
void build_la(int n)
{
	fill(vst, vst + n, 0);
	dfs2(0, -1, 0); // third parameter = root
}
int get_la(int vi, int k)
{
	int p;
	for (p = 0; k; k >>= 1, p++)
		if (k & 1)
			vi = anc[vi][p];
	return vi;
}

// vector<int> g[N];
// char vst[N];
int sz[N];
int dfs3(int vi)
{
	vst[vi] = 1;
	sz[vi] = 1;
	for (auto &vj: g[vi])
		if(!vst[vj])
			sz[vi] += dfs3(vj);
	return sz[vi];
}
void build_sz(int n)
{
	fill(vst, vst + n, 0);
	dfs3(0); // first parameter is the root
}

int main()
{
	int i, n, q;
	int vi, vj, an;
	int di, dj;
	int ani, anj;
	scanf("%d", &n);
	for (i = 1; i < n; i++)
	{
		scanf("%d%d", &vi, &vj); --vi; --vj;
		g[vi].push_back(vj);
		g[vj].push_back(vi);
	}
	build_lca(n);
	build_la(n);
	build_sz(n);
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &vi, &vj); --vi; --vj;
		an = get_lca(vi, vj);
		di = dep[dfn[vi]] - dep[dfn[an]];
		dj = dep[dfn[vj]] - dep[dfn[an]];
		if ((di + dj) & 1)
			puts("0");
		else if (vi == vj)
			printf("%d\n", n);
		else if (di == dj)
		{
			ani = get_la(vi, di - 1);
			anj = get_la(vj, dj - 1);
			printf("%d\n", n - sz[ani] - sz[anj]);
		}
		else
		{
			if (di < dj)
				swap(di, dj),
				swap(vi, vj);
			ani = get_la(vi, (di + dj) >> 1);
			anj = get_la(vi, ((di + dj) >> 1) - 1);
			printf("%d\n", sz[ani] - sz[anj]);
		}
	}
//	int i, j;
//	g[0].push_back(1); g[1].push_back(0);
//	g[1].push_back(2); g[2].push_back(1);
//	g[1].push_back(3); g[3].push_back(1);
//	g[2].push_back(4); g[4].push_back(2);
//	build_lca(5);
//	cout << get_lca(1, 4) << endl;
//	cout << get_lca(3, 4) << endl;
//	cout << get_lca(2, 3) << endl;
//	
//	build_la(5);
//	cout << get_la(3, 2) << endl;
//	cout << get_la(4, 2) << endl;
//	cout << get_la(4, 3) << endl;
//	
//	build_sz(5);
//	cout << sz[0] << endl;
//	cout << sz[2] << endl;
//	
//	while (1);
//	
//	int a[] = {2, 5, 6, 1, 2, 3, 5, 0, 4};
//	int n = sizeof(a) / sizeof(int);
//	build_rmq(a, n);
//	for (i = 0; i < n; printf(", i = %d\n", i), i++)
//		for (j = 0; j < 3; j++)
//			printf("%d ", rmq[i][j]);
//	while (cin >> i >> j)
//		cout << get_rmq(a, i, j) << endl;
	return 0;
}
