#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int L = 605;
const int I = 20; // log2(MAX_LEN) + 2, because 0 to ceil(log2(MAX_LEN)) is needed

struct suf
{
	int rk1, rk2;
	int i;
	bool operator < (const suf &rhs)const
	{
		if (rk1 != rhs.rk1)
			return rk1 < rhs.rk1;
		else
			return rk2 < rhs.rk2;
	}
	bool operator == (const suf &rhs)const
	{
		return rk1 == rhs.rk1 && rk2 == rhs.rk2;
	}
};

int rk[I][L];
int it; // number of iterations
suf tmp[L];
suf real_suf[L];
unordered_set<string> pr;

void build(const char *s, const int &len)
{
	int i, l;
	for (i = 0; i < len; i++)
		rk[0][i] = s[i];
	for (it = 1, l = 1; l < len; it++, l <<= 1)
	{
		for (i = 0; i < len; i++)
		{
			tmp[i].i = i;
			tmp[i].rk1 = rk[it - 1][i];
			tmp[i].rk2 = i + l < len ? rk[it - 1][i + l] : -1;
		}
		sort(tmp, tmp + len);
		for (i = 0; i < len; i++)
			rk[it][tmp[i].i] = tmp[i] == tmp[i - 1] ? rk[it][tmp[i - 1].i] : i;
	}
	for (i = 0; i < len; i++)
		real_suf[i] = (suf){ rk[it - 1][i], 0, i };
	sort(real_suf, real_suf + len);
}

int lcp(const char *s, const int &len, int i, int j)
{
	int k, ret = 0;
	for (k = it - 1; k >= 0 && i < len && j < len; k--)
		if (rk[k][i] == rk[k][j])
		{
			i += 1 << k;
			j += 1 << k;
			ret += 1 << k;
		}
	return ret;
}

char s[L];
int main()
{
	int i, j, l1, len, lans, cp;
	vector<int> ians;
	int tt = 0;
	while (gets(s))
	{
		pr.clear();
		if (tt++) puts("");
		lans = 0;
		l1 = strlen(s); s[l1] = -2;
		gets(&s[l1 + 1]);
		len = l1 + 1 + strlen(&s[l1 + 1]);
		build(s, len);
		for (i = 0; i < len - 1; i++)
		{
			if (s[real_suf[i].i] <= 0) continue;
			int i1 = real_suf[i].i, i2 = real_suf[i + 1].i;
			if ( (i1 < l1 && i2 < l1) || (i1 > l1 && i2 > l1) ) continue;
			if (i1 > i2) swap(i1, i2);
			cp = lcp(s, len, i1, i2);
			if (cp > lans)
			{
				lans = cp;
				ians.clear();
				ians.push_back(i1);
			}
			else if (cp == lans)
				ians.push_back(i1);
		}
		if (lans == 0)
			puts("No common sequence.");
		else
		{
//			printf("%d\n", lans);
			for (i = 0; i < ians.size(); i++)
			{
				char tmp = s[ians[i] + lans];
				s[ians[i] + lans] = '\0';
				auto it = pr.find(string(&s[ians[i]]));
				if (it == pr.end())
				{
					for (j = 0; j < lans; j++)
						putchar(s[ians[i] + j]);
					puts("");
					pr.insert(string(&s[ians[i]]));
				}
				s[ians[i] + lans] = tmp;
			}
		}
		gets(s);
	}
	return 0;
}
