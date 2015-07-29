#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

class PartitionTreeNode;
class PartitionTree;


class PartitionTreeNode
{
public:
	vector<int> y;
	vector<int> fl, fr;

	PartitionTreeNode() {}
	void resize(int _sz)
	{
		y.resize(_sz);
		fl.resize(_sz);
		fr.resize(_sz);
	}
};

class PartitionTree
{
public:
	PartitionTreeNode *nd;
	vector<pair<int, int> > ref;
	
	PartitionTree() {}
	~PartitionTree() { delete [] nd; }
	PartitionTreeNode * get_root() { return (&nd[1]); }
	void ptree_merge(int idx, int l, int r);
	int ptree_get_kth(int idx, int ql, int qr, int k);
	int get_kth(int ql, int qr, int k)
	{
		return ptree_get_kth(1, ql, qr, k);
	}
	void build(int a[], int len)
	{
		int i;
		ref.resize(len);
		nd = new PartitionTreeNode[len << 2 | 3];
		for (i = 0; i < len; i++)
		{
			ref[i].first = a[i];
			ref[i].second = i;
		}
		sort(ref.begin(), ref.end());
		ptree_merge(1, 0, len - 1);
	}
	
};

void PartitionTree::ptree_merge(int idx, int l, int r)
{
	PartitionTreeNode *t = &nd[idx];
	t->resize(r - l + 1);
	if (l == r) { t->y[0] = ref[l].second; return ; }
	PartitionTreeNode *tl = &nd[idx << 1], *tr = &nd[idx << 1 | 1];
	int i, j, k, m = (l + r) >> 1;
	int llen = m - l + 1, rlen = r - m;
	ptree_merge(idx << 1, l, m);
	ptree_merge(idx << 1 | 1, m + 1, r);
	for (i = j = k = 0; i < llen && j < rlen; k++)
	{
		t->fl[k] = i; t->fr[k] = j;
		if (tl->y[i] < tr->y[j])
			t->y[k] = tl->y[i++];
		else
			t->y[k] = tr->y[j++];
	}
	for ( ; i < llen; k++) { t->fl[k] = i; t->fr[k] = j; t->y[k] = tl->y[i++]; }
	for ( ; j < rlen; k++) { t->fl[k] = i; t->fr[k] = j; t->y[k] = tr->y[j++]; }
}

int PartitionTree::ptree_get_kth(int idx, int ql, int qr, int k)
{
	PartitionTreeNode *t = &nd[idx];
	if (ql == qr) return t->y[ql];
	PartitionTreeNode *tl = &(nd[idx << 1]), *tr = &(nd[idx << 1 | 1]);
	int l1 = t->fl[ql], l2 = t->fr[ql];
	int r1 = t->fl[qr], r2 = t->fr[qr];
	if (r1 < tl->y.size() && tl->y[r1] == t->y[qr]) --r2; else --r1;
	if (k <= r1 - l1 + 1)
		return ptree_get_kth(idx << 1, l1, r1, k);
	else
		return ptree_get_kth(idx << 1 | 1, l2, r2, k - (r1 - l1 + 1));
}

int a[100005];
int main()
{
	int i, n, q;
	int ql, qr, k;
	while (scanf("%d%d", &n, &q) == 2)
	{
		PartitionTree ptree;
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		ptree.build(a, n);
		while (q--)
		{
			scanf("%d%d%d", &ql, &qr, &k); --ql; --qr;
			printf("%d\n", a[ptree.get_kth(ql, qr, k)]);
		}
	}
	return 0;
}
