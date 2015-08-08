#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> pii;
typedef unsigned long long ull;

int sq;
ull a[200005];
pair<pii, int> rng[200005];
ull cnt[1000005];
ull ans;
ull que[200005];

bool mo_cmp(pair<pii, int> l, pair<pii, int> r)
{
	const pii &a = l.first, &b = r.first;
	return a.first / sq != b.first / sq ?
		a.first / sq < b.first / sq
		 : a.second < b.second;
}

void add(int i, int j)
{
	int k;
	for (k = i; k <= j; k++)
		cnt[a[k]]++, ans += (2 * cnt[a[k]] - 1) * a[k];
}

void rem(int i, int j)
{
	int k;
	for (k = i; k <= j; k++)
		cnt[a[k]]--, ans -= (2 * cnt[a[k]] + 1) * a[k];
}

int main()
{
	int i, n, q;
	int prev_l, prev_r;
	ans = 0;
	scanf("%d%d", &n, &q); sq = sqrt(n);
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	for (i = 0; i < q; rng[i].second = i, rng[i].first.first--, rng[i].first.second--, i++) scanf("%d%d", &rng[i].first.first, &rng[i].first.second);
	sort(rng, rng + q, mo_cmp);
	prev_l = prev_r = 0; add(0, 0);
	for (i = 0; i < q; prev_l = rng[i].first.first, prev_r = rng[i].first.second, i++)
	{
		int &l = rng[i].first.first, &r = rng[i].first.second;
		if (r >= prev_r) add(prev_r + 1, r); else rem(r + 1, prev_r);
		if (l >= prev_l) rem(prev_l, l - 1); else add(l, prev_l - 1);
		que[rng[i].second] = ans;
	}
	for (i = 0; i < q; i++)
		printf("%I64u\n", que[i]);
	return 0;
}