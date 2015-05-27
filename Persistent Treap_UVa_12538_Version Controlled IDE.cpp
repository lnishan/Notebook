#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define ROOT root[root_iter]

using namespace std;

const int MAX_VER = 50002;
const int MAX_LEN = 105;

struct treap;
int size(treap *);

struct treap
{
	char val;
	int pri, sz;
	treap *l, *r;
	treap(int _val = 0): val(_val), pri(rand()), sz(1), l(NULL), r(NULL){}

	void pull()
	{
		sz = size(l) + size(r) + 1;
	}
};
treap *root[MAX_VER];
int root_iter;
int cnt_c;
char s[MAX_LEN];

int size(treap *t) { return t ? t->sz : 0; }

treap * copy(treap *t)
{
	treap *n = new treap;
	*n = *t;
	return n;
}

void in(treap *t)
{
	if (!t) return ;
	in(t->l);
	putchar(t->val);
	if (t->val == 'c') cnt_c++;
	in(t->r);
}

void split(treap *t, const int &rk, treap * &l, treap * &r)
{
	if (!t) { l = r = NULL; return ; }
	treap *t2 = copy(t);
	if (size(t->l) < rk)
	{
		l = t2;
		split(t2->r, rk - size(t->l) - 1, t2->r, r);
	}
	else
	{
		r = t2;
		split(t2->l, rk, l, t2->l);
	}
	t2->pull();
}

treap * merge(treap *l, treap *r)
{
	if (!l) return r;
	if (!r) return l;
	if (l->pri > r->pri)
	{
		treap *n = copy(l);
		n->r = merge(n->r, r);
		n->pull();
		return n;
	}
	else
	{
		treap *n = copy(r);
		n->l = merge(l, n->l);
		n->pull();
		return n;
	}
}

void _split(treap *t, const int &rk, treap * &l, treap * &r)
{
	if (!t) { l = r = NULL; return ; }
	if (size(t->l) < rk)
	{
		l = t;
		split(t->r, rk - size(t->l) - 1, t->r, r);
	}
	else
	{
		r = t;
		split(t->l, rk, l, t->l);
	}
	t->pull();
}

treap * _merge(treap *l, treap *r)
{
	if (!l) return r;
	if (!r) return l;
	if (l->pri > r->pri)
	{
		l->r = merge(l->r, r);
		l->pull();
		return l;
	}
	else
	{
		r->l = merge(l, r->l);
		r->pull();
		return r;
	}
}

void insert(char s[], int len, int pos) // insert after pos
{
	int i;
	treap *l, *r, *n, *ins = NULL;
	split(ROOT, pos, l, r);
	++root_iter;
	for (i = 0; i < len; i++)
	{
		n = new treap;
		n->val = s[i];
		ins = _merge(ins, n);
	}
	ROOT = merge(l, ins);
	ROOT = merge(ROOT, r);
}

void remove(const int &st, const int &len)
{
	treap *l, *r, *ll, *lr;
	split(ROOT, st+len-1, l, r);
	split(l, st-1, ll, lr);
	++root_iter;
	ROOT = merge(ll, r);
}

void print(const int &ver, const int &st, const int &len)
{
	treap *l, *r, *ll, *lr;
	treap *&rt = root[ver];
	_split(rt, st+len-1, l, r);
	_split(l, st-1, ll, lr);
	in(lr); puts("");
	rt = _merge(ll, lr);
	rt = _merge(rt, r);
}

void init()
{
	srand(time(0));
	memset(root, 0, sizeof(root));
	root_iter = 0; // can be -1
	cnt_c = 0;
}

int main()
{
	int i, qs, cmd, pos, len, ver, l;
	init();
	scanf("%d", &qs);
	while (qs--)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
			case 1:
				scanf("%d %s", &pos, s);
				l = strlen(s);
				pos -= cnt_c;
				insert(s, l, pos + i);
				break;
			case 2:
				scanf("%d %d", &pos, &len);
				pos -= cnt_c;
				len -= cnt_c;
				remove(pos, len);
				break;
			case 3:
				scanf("%d %d %d", &ver, &pos, &len);
				ver -= cnt_c;
				pos -= cnt_c;
				len -= cnt_c;
				print(ver, pos, len);
				break;
		}
	}
	return 0;
}
