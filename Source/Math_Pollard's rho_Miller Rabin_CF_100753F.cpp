#include <cstdio>
#include <map>
#include <algorithm>

using namespace std;
typedef long long ll;

map<ll, int> fact;
ll mul(ll a, ll b, ll n) { // a*b%n
    ll r = 0;
    a %= n, b %= n;
    while(b){
        if( b&1 ) r = a+r>=n ? a+r-n : a+r;
        a = a+a>=n ? a+a-n : a+a;
        b >>= 1;
    }
    return r;
}
ll powmod(ll a, ll d, ll n) { // a^d%n
    if(d==0) return 1ll;
    if(d==1) return a%n;
    return mul(powmod(mul(a, a, n), d>>1, n), d%2?a:1, n);
}
bool miller_rabin(ll n, ll a) {
    if(__gcd(a,n)==n) return true;
    if(__gcd(a,n)!=1) return false;
    ll d = n-1, r = 0, res;
    while(d%2==0) { ++r; d>>=1; }
    res = powmod(a, d, n);
    if(res==1||res==n-1) return true;
    while(r--) {
        res = mul(res, res, n);
        if(res==n-1) return true;
    }
    return false;
}
bool isPrime(ll n) {
    ll as[7]={2, 325, 9375, 28178, 450775, 9780504, 1795265022}; //  2, 7, 61
    for(int i=0; i<7; i++)
        if( !miller_rabin(n, as[i]) )
            return false;
    return true;
}
void pollardrho(long long n)
{
    if(n==1) return;
    if(isPrime(n))
	{
        fact[n]++;
        return;
    }
    if(!(n&1))
	{
        fact[2]++;
        pollardrho(n>>1);
        return;
    }
    while(1)
    {
        long long a = rand()%n;
        long long b = a;
        long long c = rand()%(n-1)+1;
        while(1)
        {
            a = (mul(a, a, n)+c)%n;
            b = (mul(b, b, n)+c)%n;
            b = (mul(b, b, n)+c)%n;
            long long g = __gcd(abs(a-b),n);
            if(g==n) break;
            if(g>1)
            {
                if (isPrime(g)) fact[g]++;
                else pollardrho(g);
                pollardrho(n/g);
                return;
            }
        }
    }
}
int main()
{
    long long n;
    scanf("%lld",&n);
    pollardrho(n);
    int ans=1;
    for(map<ll, int>::iterator it=fact.begin();it!=fact.end();it++)
        ans*=it->second+1;
    printf("%d\n",ans);
    return 0;
}
