#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 5005;

struct pt
{
	int x, y;
} a[N];
int n;
int stk[N], top;

bool cmp(pt a, pt b)
{
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}

int cross(pt c, pt b, pt a)
{
	int dx1 = c.x - b.x, dy1 = c.y - b.y;
	int dx2 = b.x - a.x, dy2 = b.y - a.y;
	return dx1 * dy2 - dy1 * dx2;
}

double dist(pt a, pt b)
{
	int dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

void mtone()
{
	int i, j, fhalf;
	top = 0;
	sort(a, a + n, cmp);
	for (i = 0; i < n; i++)
	{
		if (top < 2)
			stk[++top] = i;
		else
		{
			while (top >= 2 && cross(a[i], a[stk[top]], a[stk[top - 1]]) >= 0) --top;
			stk[++top] = i;
		}
	}
	fhalf = top;
	for (i = n - 1; i >= 0; i--)
	{
		if (top - fhalf < 2)
			stk[++top] = i;
		else
		{
			while (top - fhalf >= 2 && cross(a[i], a[stk[top]], a[stk[top - 1]]) >= 0) --top;
			stk[++top] = i;
		}
	}
}

int main()
{
	int i, t;
	double ans;
	scanf("%d", &t);
	while (t--)
	{
		ans = 0;
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d%d", &a[i].x, &a[i].y);
		mtone();
		for (i = 1; i < top; i++)
			ans += dist(a[stk[i]], a[stk[i + 1]]);
		printf("%.3f\n", ans);
	}
	return 0;
}
