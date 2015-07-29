#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int V = 1502;

struct vert
{
    int x, y;
    bool operator < (const vert &rhs)const
    {
        if (x != rhs.x)
            return x < rhs.x;
        else
            return y < rhs.y;
    }
    vert operator - (const vert &rhs)const
    {
        vert tmp;
        tmp.x = x - rhs.x;
        tmp.y = y - rhs.y;
        return tmp;
    }
    void operator = (const vert &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
} a[V], r[V];
char used[V][V];

int cross(const vert &a, const vert &b)
{
    return a.x * b.y - a.y * b.x;
}

void monotone_chain(int v, vert a[], int &vr, vert r[])
{
    int i, j;
    vert *f = new vert[v]; int it_f = 0;
    vert *b = new vert[v]; int it_b = 0;
    sort(a, a+v);
    for (i = 0; i < v; i++)
        if (it_f < 2)
            f[it_f++] = a[i];
        else
        {
            while (it_f >= 2 && cross(a[i]-f[it_f-1], f[it_f-1]-f[it_f-2]) <= 0) it_f--;
            f[it_f++] = a[i];
        }
    for (i = v-1; i >= 0; i--)
        if (it_b < 2)
            b[it_b++] = a[i];
        else
        {
            while (it_b >= 2 && cross(a[i]-b[it_b-1], b[it_b-1]-b[it_b-2]) <= 0) it_b--;
            b[it_b++] = a[i];
        }
    for (i = 0, j = 0; i < it_f-1; i++)
        r[j++] = f[i];
    for (i = 0; i < it_b-1; i++)
        r[j++] = b[i];
    vr = j;
    delete [] f;
    delete [] b;
}

int main()
{
    int i, t, tmp_v, v, vr, min_idx;
    memset(used, 0, sizeof(used));
    scanf("%d", &t);
    printf("%d\n", t);
    while (t--)
    {
    	v = 0;
        scanf("%d", &tmp_v);
        for (i = 0; i < tmp_v; i++)
        {
            scanf("%d%d", &a[v].x, &a[v].y);
            if (!used[a[v].x][a[v].y])
            {
            	used[a[v].x][a[v].y] = 1;
            	v++;
            }
        }

        monotone_chain(v, a, vr, r);

        printf("%d\n", vr + 1);
        for (i = 0; i < vr; i++)
            printf("%d %d\n", r[i].x , r[i].y);
        
    }
    return 0;
}
