#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define MAX_N 100005
#define MAX_M 50005

using namespace std;

struct treap;
int size(treap* &);

struct treap
{
	int pri;
	int key, size;
	treap *chi[2];
	treap(): pri(rand()), size(1) { chi[0] = chi[1] = NULL; }
	
	void pull()
	{
		size = ::size(chi[0]) + ::size(chi[1]) + 1;
	}
} *root = NULL;

struct range
{
	int i;
	int l, r, rk;
	bool operator < (const range &rhs)const
	{
		return l < rhs.l;
	}
} r[MAX_M]; 
int out[MAX_M];

int size(treap* &cur)
{
	return cur ? cur -> size : 0;
}

void split(treap *cur, const int &key, treap* &l, treap* &r)
{
	if (!cur) { l = r = NULL; return ; }
	if (cur->key <= key)
	{
		l = cur;
		split(l->chi[1], key, l->chi[1], r);
		l->pull();
	}
	else
	{
		r = cur;
		split(r->chi[0], key, l, r->chi[0]);
		r->pull();
	}
}

treap * merge(treap *l, treap *r) // l->key < r->key, for all children
{
	if (!l) return r;
	if (!r) return l;
	if (l->pri > r->pri)
	{
		l->chi[1] = merge(l->chi[1], r);
		l->pull();
		return l;
	}
	else
	{
		r->chi[0] = merge(l, r->chi[0]);
		r->pull();
		return r;
	}
}

void insert(const int &key)
{
	if (root == NULL) { root = new treap; root->key = key; return ; }
	treap *l, *r, *n = new treap;
	n->key = key;
	split(root, key, l, r);
	root = merge(l, n);
	root = merge(root, r);
}

void build(int a[], int len)
{
	int i;
	for (i = 0; i < len; i++)
		insert(a[i]);
}

void del(const int &key)
{
	treap *l, *r, *ll, *lr, *n;
	split(root, key, l, r);
	if (!l) return ;
	// if exists key
	split(l, key-1, ll, lr);
	// drop 1 from lr
	n = merge(lr->chi[0], lr->chi[1]); // can be null
	n = merge(ll, n); // can be null
	root = merge(n, r);
	delete lr;
}

treap *getRk(int rk, treap* &cur)
{
	int myRk = size(cur->chi[0]) + 1;
	if (myRk == rk) return cur;
	if (myRk < rk)
		return getRk(rk - myRk, cur->chi[1]);
	else
		return getRk(rk, cur->chi[0]);
}

void pre(treap *n)
{
	if (!n) return ;
	printf("%d(%d) ", n->key, size(n));
	pre(n->chi[0]);
	pre(n->chi[1]);
}

void in(treap *n)
{
	if (!n) return ;
	in(n->chi[0]);
	printf("%d(%d) ", n->key, size(n));
	in(n->chi[1]);
}

int a[MAX_N];
int main()
{
	int i, j, n, m, prev_l, prev_r, lb, ub;
	treap *ans;
	srand(time(0));
	
	scanf("%d%d", &n, &m);
	if (!m) return 0;
	
	for (i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	// root = NULL, declared above
	for (i = 0; i < m; i++)
	{
		r[i].i = i;
		scanf("%d%d%d", &r[i].l, &r[i].r, &r[i].rk);
	}
	sort(r, r + m);
	
	for (i = r[0].l; i <= r[0].r; i++)
		insert(a[i]);
	ans = getRk(r[0].rk, root);
	// in(root); puts("");
	out[r[0].i] = ans->key;
	prev_l = r[0].l;
	prev_r = r[0].r;
	for (i = 1; i < m; prev_l = r[i].l, prev_r = r[i].r, i++)
	{
		range &ri = r[i];
		ub = min(ri.l - 1, prev_r);
		for (j = prev_l; j <= ub; j++)
			del(a[j]);
		lb = max(ri.l, prev_r + 1);
		for (j = lb; j <= ri.r; j++)
			insert(a[j]);
		ans = getRk(ri.rk, root);
		out[ri.i] = ans->key;
	}
	for (i = 0; i < m; i++)
		printf("%d\n", out[i]);
	return 0;
}
