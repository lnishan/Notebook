#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 2e5 + 5;

int n;
double a[N];

double max_poor(double x)
{
	int i;
	double pre, mpre, ret = 0;
	// get max-subarray
	pre = mpre = 0;
	for (i = 0; i < n; i++)
	{
		pre += a[i] - x;
		ret = max(ret, abs(pre - mpre));
		mpre = min(mpre, pre);
	}
	// get min-subarray
	pre = mpre = 0;
	for (i = 0; i < n; i++)
	{
		pre += a[i] - x;
		ret = max(ret, abs(pre - mpre));
		mpre = max(mpre, pre);
	}
	return ret;
}

int main()
{
	cin.tie(0);
	ios::sync_with_stdio(0);
	int i;
	double l = 0.0, h = 0.0, m1, m2;
	cin >> n;
	for (i = 0; i < n; h = max(h, abs(a[i])), i++) cin >> a[i];
	l = -h;
	for (i = 0; i < 300; i++)
	{
		m1 = l + (h - l) / 3;
		m2 = h - (h - l) / 3;
		if (max_poor(m1) > max_poor(m2))
			l = m1;
		else
			h = m2;
	}
	printf("%.17f\n", max_poor(l));
	return 0;
}
