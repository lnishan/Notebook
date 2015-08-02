#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 100005;
const int lgN = 25;

int rmq[N][lgN];
void build_rmq(int a[], int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		rmq[i][0] = a[i];
		for (j = 1; i - (1 << j) + 1 >= 0; j++)
			rmq[i][j] = min(rmq[i][j - 1], rmq[i - (1 << (j - 1))][j - 1]);
	}
}
int get_rmq(int i, int j)
{
	if (i > j) swap(i, j);
	int k, l = j - i + 1;
	for (k = 0; (1 << k) <= l; k++) ; --k;
	return min(rmq[i + (1 << k) - 1][k], rmq[j][k]);
}

int main()
{
	int i, j;
	int a[] = {2, 5, 6, 1, 2, 3, 5, 0, 4};
	int n = sizeof(a) / sizeof(int);
	build_rmq(a, n);
	for (i = 0; i < n; printf(", i = %d\n", i), i++)
		for (j = 0; j < 3; j++)
			printf("%d ", rmq[i][j]);
	while (cin >> i >> j)
		cout << get_rmq(i, j) << endl;
	return 0;
}

/*
 * RMQ that returns the index of the minimum item
 * 
int rmq[N][lgN];
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

int main()
{
	int i, j;
	int a[] = {2, 5, 6, 1, 2, 3, 5, 0, 4};
	int n = sizeof(a) / sizeof(int);
	build_rmq(a, n);
	for (i = 0; i < n; printf(", i = %d\n", i), i++)
		for (j = 0; j < 3; j++)
			printf("%d ", rmq[i][j]);
	while (cin >> i >> j)
		cout << get_rmq(a, i, j) << endl;
	return 0;
}*/
