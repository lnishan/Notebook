#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

const int R = 502;
const int C = 502;

int r, c;
int a[R][C], s[R][C];

int query(int x, int y)
{
	int yy, ret = 0;
	while (x >= 1)
	{
		yy = y;
		while (yy >= 1)
		{
			ret += s[x][yy];
			yy -= yy & (-yy);
		}
		x -= x & (-x);
	}
	return ret;
}
void update(int x, int y, int v)
{
	int yy;
	while (x <= r)
	{
		yy = y;
		while (yy <= c)
		{
			s[x][yy] += v;
			yy += yy & (-yy);
		}
		x += x & (-x);
	}
}
void init()
{
	memset(s, 0, sizeof(s));
}

int main()
{
	int i, j;
	while (cin >> r >> c)
	{
		init();
		for (i = 1; i <= r; i++)
			for (j = 1; j <= c; j++)
			{
				scanf("%d", &a[i][j]);
				update(i, j, a[i][j]);
			}
		cout << query(r, c) << endl;
	}
	return 0;
}
