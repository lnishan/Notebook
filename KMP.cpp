#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int L = 200005;

void cal_fail(char s[], int len, int f[])
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		j = i - 1;
		while (j > -1 && s[f[j] + 1] != s[i]) j = f[j];
		f[i] = j > -1 ? f[j] + 1 : -1;
	}
}

int kmp(char s[], int len, char p[], int plen, int f[])
{
	int i, j;
	for (i = 0, j = 0; i < len; i++)
	{
		while (j > -1 && s[i] != p[j]) j = j ? f[j - 1] + 1 : -1;
		if (++j == plen) return i; // j = f[j - 1] + 1
	}
	return -1;
}

char s[L], *p;
int f[L];

int main()
{
	int i, len;
	while (gets(s))
	{
		len = strlen(s);
		for (i = 0; i < len; i++)
			s[len + i] = s[len - i - 1];
		p = &s[len]; p[len] = '\0';
		puts(p);
		cal_fail(p, len, f);
		for (i = 0; i < len; i++)
			printf("%d ", f[i]);
		puts("");
//		len <<= 1;
//		s[len] = '\0';
//		puts(s);
		
	}
	return 0;
}
