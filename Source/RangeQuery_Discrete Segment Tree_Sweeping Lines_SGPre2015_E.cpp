#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;
typedef long long ll;

const int N = 1e6 + 5;
const int X = 2e6 + 5;
const int S = 1e6;

vector<int> x, y;
int lx[X], ly[X];

struct node
{
	int mx, mxs, cov;
} s[N << 3];

struct event
{
	int x;
	int y1, y2;
	int u; // 1 for add, 0 for substract
	bool operator < (const event &rhs)const
	{
		if (x != rhs.x)
			return x < rhs.x;
		else
			return u > rhs.u;
	}
};
vector<event> a, m;

void build(int i, int l, int r)
{
	s[i].mx = s[i].cov = 0;
	s[i].mxs = y[r] - y[l]; // change
	if (r - l == 1) return ;
	int m = (l + r) >> 1;
	build(i << 1, l, m);
	build(i << 1 | 1, m, r);
}

int upd(int i, int l, int r, int ql, int qr, int u)
{
	if (qr <= l || ql >= r) return s[i].mx + s[i].cov;
	if (ql <= l && r <= qr)
	{
		s[i].cov += u;
		return s[i].mx + s[i].cov;
	}
	int m = (l + r) >> 1;
	s[i].mx = max(upd(i << 1, l, m, ql, qr, u), upd(i << 1 | 1, m, r, ql, qr, u));
	// printf("[%d, %d]\n", l, r);
	// printf("%d %d\n", s[i << 1].mx + s[i << 1].cov, s[i << 1].mxs);
	// printf("%d %d\n", s[i<<1|1].mx + s[i<<1|1].cov, s[i<<1|1].mxs);
	s[i].mxs = s[i << 1].mx + s[i << 1].cov == s[i].mx ? s[i << 1].mxs : 0;
	s[i].mxs += s[i<<1|1].mx + s[i<<1|1].cov == s[i].mx ? s[i<<1|1].mxs : 0;
	// printf("s[%d].mx = %d, s[%d].mxs = %d, s[%d].cov = %d\n", i, s[i].mx, i, s[i].mxs, i, s[i].cov);
	return s[i].mx + s[i].cov;
}

int main()
{
	int i, tt, n, x1, y1, x2, y2, c;
	int xx, ai, mi;
	ll ans, anss;
	scanf("%d", &tt);
	while (tt--)
	{
		scanf("%d", &n);
		x.clear(); x.reserve(n << 1);
		y.clear(); y.reserve(n << 1);
		a.clear(); a.reserve(n << 1);
		m.clear(); m.reserve(n << 1);
		ai = mi = 0;
		ans = 0;
		for (i = 0; i < n; i++)
		{
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
			x.push_back(x1); x.push_back(x2);
			y.push_back(y1); y.push_back(y2);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			a.push_back( (event){x1, y1, y2, c} );
			m.push_back( (event){x2, y1, y2, -c} );
		}
		sort(x.begin(), x.end());
		sort(y.begin(), y.end());
		unique(x.begin(), x.end());
		unique(y.begin(), y.end());
		for (i = 0; i < x.size(); i++)
			lx[x[i] + S] = i;
		for (i = 0; i < y.size(); i++)
			ly[y[i] + S] = i;
		// for (i = 0; i < x.size(); i++)
		//	printf("%d %d\n", i, x[i]);
		sort(a.begin(), a.end());
		sort(m.begin(), m.end());
		build(1, 0, y.size() - 1);
		for (xx = 1; xx < x.size(); xx++)
		{
//			puts("*");
			while (ai < a.size() && lx[a[ai].x + S] < xx)
			{
				upd(1, 0, y.size() - 1, ly[a[ai].y1 + S], ly[a[ai].y2 + S], a[ai].u);
				ai++;
			}
			while (mi < m.size() && lx[m[mi].x + S] < xx)
			{
				upd(1, 0, y.size() - 1, ly[m[mi].y1 + S], ly[m[mi].y2 + S], m[mi].u);
				mi++;
			}
			if (s[1].mx + s[1].cov > ans)
			{
				ans = s[1].mx + s[1].cov;
				anss = (ll)s[1].mxs * (x[xx] - x[xx - 1]);
			}
			else if (s[1].mx + s[1].cov == ans)
				anss += (ll)s[1].mxs * (x[xx] - x[xx - 1]);
		}
		printf("%lld %lld\n", ans, anss);
	}
	return 0;
}
