#include <cstdio>
#include <cstring>
#define MAXL 1000

using namespace std;

void pre(char *pat, int* &f)
{
	int i, j, l=strlen(pat);
	f = new int[l];
	f[0] = -1;
	for (i = 1; i < l; i++)
	{
		j = i-1;
		while (pat[f[j]+1] != pat[i])
		{
			j = f[j];
			if (j == -1)
				break;
		}
		f[i] = (j == -1) ? -1 : f[j]+1;
	}
	return ;
}

void KMP(char *s, char *pat)
{
	int i, j, *f, ls=strlen(s), lp=strlen(pat);
	pre(pat, f);
	for (i = 0, j = 0; i < ls; )
	{
		if (s[i] == pat[j])
		{
			i++;
			j++;
			if (j == lp)
			{
				printf("found at %d\n", i-lp);
				j = f[j-1] + 1;
			}
		}
		else
		{
			if (j == 0)
				i++;
			else
				j = f[j-1] + 1;
		}
	}
	return ;
}

int main()
{
	char s[MAXL+1], pat[MAXL+1]; // char *pat="abcaabcacab";
	gets(pat);
	while( gets(s) )
		KMP(s, pat);
	return 0;
}
