#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

struct treap;
int size(treap *&);

#define L(X) X->c[0^accu_rev]
#define R(X) X->c[1^accu_rev]
struct treap
{
	int val, pri, sz;
	int mi, add;
	char rev;
	treap *c[2];
	treap(int _val = 0): val(_val), sz(1), pri(rand()), mi(_val), add(0), rev(0)
	{
		c[0] = c[1] = NULL;
	}
	void push(char &_rev)
	{
		_rev ^= rev;
	}
	void pull()
	{
		sz = size(c[0]) + size(c[1]) + 1;
		mi = val;
		if (c[0]) mi = min(mi, c[0]->mi + c[0]->add);
		if (c[1]) mi = min(mi, c[1]->mi + c[1]->add);
	}
} *root = NULL;

int size(treap *&t) { return t ? t->sz : 0; }

void split(treap *t, int rk, treap *&l, treap *&r, char accu_rev = 0)
{
	if (!t) { l = r = NULL; return ; }
	t->push(accu_rev);
	treap *&tl = L(t), *&tr = R(t);
	if (size(tl) < rk)
	{
		l = t;
		split(tr, rk - size(tl) - 1, tr, r, accu_rev);
		if (r) {
			r->add += t->add;
			r->rev ^= t->rev;
		}
	}
	else
	{
		r = t;
		split(tl, rk, l, tl, accu_rev);
		if (l) {
			l->add += t->add;
			l->rev ^= t->rev;
		}
	}
	t->pull();
}

treap * merge(treap *&l, treap *&r, char accu_rev_l = 0, char accu_rev_r = 0)
{
	if (!l) return r;
	if (!r) return l;
	l->push(accu_rev_l);
	r->push(accu_rev_r);
	if (l->pri > r->pri)
	{
		r->add -= l->add;
		r->rev ^= l->rev;
		char &accu_rev = accu_rev_l;
		r->push(accu_rev_r);
		R(l) = merge(R(l), r, accu_rev_l, accu_rev_r);
		l->pull();
		return l;
	}
	else
	{
		l->add -= r->add;
		l->rev ^= r->rev;
		char &accu_rev = accu_rev_r;
		l->push(accu_rev_l);
		L(r) = merge(l, L(r), accu_rev_l, accu_rev_r);
		r->pull();
		return r;
	}
}

void insert(const int &val, const int &pos) // pos = [1,]
{
	treap *l, *r, *n = new treap;
	n->val = n->mi = val;
	split(root, pos-1, l, r);
	root = merge(l, n);
	root = merge(root, r);
}

void del(const int &rk)
{
	treap *l, *r, *ll, *lr;
	split(root, rk, l, r);
	split(l, rk-1, ll, lr);
	root = merge(ll, r);
	delete lr;
}

int query(int type, int i, int j, int n = 0) // i, j = [1,]
{
	int ret;
	treap *l, *r, *rl, *rr;
	if (i > j) swap(i, j);
	split(root, i-1, l, r);
	split(r, j-i+1, rl, rr);
	switch (type)
	{
		case 0: // min
			ret = rl->mi + rl->add;
			break;
		case 1: // add
			rl->add += n;
			ret = 1; //meaningless
			break;
		case 2: // reverse
			rl->rev ^= 1;
			ret = 1;
			break;
		case 3: // revolve
			n %= (j - i + 1);
			treap *ql, *qr;
			split(rl, j - i + 1 - n, ql, qr);
			rl = merge(qr, ql);
			ret = 1;
			break;
	}
	root = merge(rl, rr);
	root = merge(l, root);
	return ret;
}

void in(treap *t, char accu_rev = 0)
{
	if (!t) return ;
	t->push(accu_rev);
	in(L(t), accu_rev);
	printf("%d(%d) ", t->val, size(t));
	in(R(t), accu_rev);
	return ;
}

int main()
{
	int i, j, n, m, ai, qi, qj, qn;
	char s[100], cmd[20];
	srand(time(0));
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &ai);
		insert(ai, i);
	}
	scanf("%d", &m);
	while (m--)
	{
		scanf(" ");
		gets(s);
		sscanf(s, "%s", cmd);
		if (strcmp(cmd, "ADD") == 0)
		{
			sscanf(s, "%s %d %d %d", cmd, &qi, &qj, &qn);
			query(1, qi, qj, qn);
		}
		else if (strcmp(cmd, "REVERSE") == 0)
		{
			sscanf(s, "%s %d %d", cmd, &qi, &qj);
			query(2, qi, qj);
		}
		else if (strcmp(cmd, "REVOLVE") == 0)
		{
			sscanf(s, "%s %d %d %d", cmd, &qi, &qj, &qn);
			query(3, qi, qj, qn);
		}
		else if (strcmp(cmd, "INSERT") == 0)
		{
			sscanf(s, "%s %d %d", cmd, &qi, &qn);
			insert(qn, qi+1);
		}
		else if (strcmp(cmd, "DELETE") == 0)
		{
			sscanf(s, "%s %d", cmd, &qn);
			del(qn);
		}
		else if (strcmp(cmd, "MIN") == 0)
		{
			sscanf(s, "%s %d %d", cmd, &qi, &qj);
			printf("%d\n", query(0, qi, qj));
		}
	}
	return 0;
}
