#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;

typedef unsigned long long ull;

const int K = 10;
const int M = 100002;

int n, m, k;
int pt;
int p[K], pi[M]; // pi[prime] = index
int inv[K][M];
ull r[K];

int ex_gcd(int a, int b, int &x, int &y)
{
	if (b == 0) { x = 1; y = 0; return a; }
	int x1, y1, g = ex_gcd(b, a % b, y1, x1);
	x = x1;
	y = y1 - a / b * x1;
	return g;
}
int mod_inv(int a, int p)
{
	int x, y, g;
	g = ex_gcd(a, p, x, y);
	if (x < 0)
	{
		int dx = p / g;
		x = (x + dx * ((-x) / dx + 1)) % dx;
	}
	return x;
}
ull c_small(int n, int m, int p) // pi = the ith prime in the input
{
	if (n < m) return 0;
	int i; ull ret = 1;
	if (m >= (n >> 1)) m = n - m;
	for (i = 1; i <= m; i++)
	{
		ret = (ret * (n - i + 1)) % p;
		ret = (ret * inv[pi[p]][i]) % p;
	}
	return ret;
}
ull lucas(int n, int m, int p)
{
	ull ret = 1;
	for ( ; n | m; n /= p, m /= p)
		ret = (ret * c_small(n % p, m % p, p)) % p;
	return ret;
}
void cal_inv()
{
	int i, j;
	for (i = 0; i < k; i++)
		for (j = 1; j <= p[i]; j++)
			inv[i][j] = mod_inv(j, p[i]);
}
ull crt() // (int r[], int k, int p[])
{
	int i;
	ull ret = 0;
	int pt = 1, pti;
	// calculate pi
	for (i = 0; i < k; i++) pt *= p[i];
	// crt start
	for (i = 0; i < k; i++)
	{
		pti = pt / p[i];
		ret += (ull)r[i] * pti * mod_inv(pti, p[i]);
		ret %= pt;
	}
	return ret;
}
int main()
{
	int i, tt;
	scanf("%d", &tt);
	while (tt--)
	{
		scanf("%d%d%d", &n, &m, &k);
		for (i = 0; i < k; pi[p[i]] = i, i++) scanf("%d", &p[i]);
		cal_inv();
		for (i = 0; i < k; i++) r[i] = lucas(n, m, p[i]);
		printf("%llu\n", crt());
	}
	return 0;
}
