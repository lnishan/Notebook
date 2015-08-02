/* Arrays numbered from 1 */

#include <cstdio>
#include <cstring>
#define MAX 100002

using namespace std;

int a[MAX], fenwick[MAX], maxIdx;

int query(int idx)
{
	int sum = 0;
	while (idx > 0)
	{
		sum += fenwick[idx];
		idx -= idx & (-idx);
	}
	return sum;
}

void update(int idx, int n)
{
	while (idx <= maxIdx)
	{
		fenwick[idx] += n;
		idx += idx & (-idx);
	}
	return ;
}

int main()
{
	int i;
	memset(fenwick, 0, sizeof(fenwick));
	maxIdx = 5;
	for (i = 1; i <= 5; i++)
		update(i, +i);
	for (i = 1; i <= 5; i++)
		printf("%d\n", query(i));
	return 0;
}
