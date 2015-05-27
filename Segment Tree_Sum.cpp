#include <cstdio>
#include <algorithm>
#define MAX 100002

using namespace std;

struct node
{
	int l, r; long long int val, add;
	int left, right;
} seg[MAX<<1];

int a[MAX], t=0;
long long int buildSegmentTree(int idx, int l, int r)
{
	seg[idx].l = l;
	seg[idx].r = r;
	seg[idx].add=0;
	if (l == r)
	{
		seg[idx].val = a[l];
		return a[l];
	}
	int m = (l+r)>>1;
	seg[idx].left = ++t;
	seg[idx].right = ++t;
	seg[idx].val = buildSegmentTree(seg[idx].left, l, m) + buildSegmentTree(seg[idx].right, m+1, r);
	return seg[idx].val;
}

long long int query(int idx, int ql, int qr)
{
	int &l = seg[idx].l, &r = seg[idx].r, m = (l+r)>>1;
	
	if (ql == l && qr == r)
		return seg[idx].val + seg[idx].add * (r-l+1);
	
	long long int sum=0;
	if (ql <= m)
		sum += query(seg[idx].left, ql, min(qr, m) );
	if (qr > m)
		sum += query(seg[idx].right, max(ql, m+1), qr);
	return sum + seg[idx].add * (qr-ql+1);
}

long long int update(int idx, int ul, int ur, int n)
{
	int &l = seg[idx].l, &r = seg[idx].r, m = (l+r)>>1;
	
	if (ul == l && ur == r)
	{
		seg[idx].add += n;
		return seg[idx].val + seg[idx].add * (r-l+1);
	}
	
	long long int sum=0;
	if (ul <= m)
		sum += update(seg[idx].left, ul, min(ur, m), n);
	else
		sum += seg[seg[idx].left].val + seg[seg[idx].left].add * (seg[seg[idx].left].r-seg[seg[idx].left].l+1);
	if (ur > m)
		sum += update(seg[idx].right, max(ul, m+1), ur, n);
	else
		sum += seg[seg[idx].right].val + seg[seg[idx].right].add * (seg[seg[idx].right].r-seg[seg[idx].right].l+1);
	seg[idx].val = sum;
	
	return sum + seg[idx].add * (r-l+1);
}

int main()
{
	int i, l, r, add, n;
	for( i=0; i<=5; i++ )
		a[i]=i;
	buildSegmentTree(0, 0, 5);
	/*
	for( i=0; i<=t; i++ )
	{
		puts("-");
		printf("Index: %d\n", i);
		printf("L: %d, R: %d\n", seg[i].l, seg[i].r);
		printf("Val: %lld\n", seg[i].val);
		printf("Add: %lld\n", seg[i].add);
	}*/
	scanf("%d", &n); // n updates
	while( n-- )
	{
		scanf("%d%d%d", &l, &r, &add);
		update(0, l, r, add);
	}
	/*
	for( i=0; i<=t; i++ )
	{
		puts("-");
		printf("Index: %d\n", i);
		printf("L: %d, R: %d\n", seg[i].l, seg[i].r);
		printf("Val: %lld\n", seg[i].val);
		printf("Add: %lld\n", seg[i].add);
	}*/
	while( scanf("%d%d", &l, &r)==2 )
		printf("%lld\n", query(0, l, r));
	return 0;
}
