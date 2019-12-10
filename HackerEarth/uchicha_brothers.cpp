#include <bits/stdc++.h>
#define maxn (1<<20) + 5
#define mod 1000000007
#define num_bits first
#define broj second
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;

/**
    We use some over supersets technique in order to compute how many ways there are to choose a set s.t. all its elements' masks contain
    some fixed x as a submask (that number is uni[x]). Then, we use some over subsets again and inclusion-exclusion principle in order
    to compute how many ways there are to choose a set s.t. and of all its elements is exactly some fixed number x (that number is also 
    stored in uni[x] since we have to use the previous value to compute it).
**/

ll uni[maxn]; 
ll f[22];

int m;
int broj(string s)
{
    int res=0;
    for(int i=0;i<m;i++)
    {
        res *= 2;
        res += s[i]-'0';
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin>>n>>m;

    int MAXX = (1<<m) - 1;
    for(int i=0;i<=MAXX;i++)uni[i]=1;

    string s;
    for(int i=0;i<n;i++)
    {
        ll cost;
        cin>>cost>>s;
        int br = broj(s);
        uni[ br ] *= (1 + cost);
        uni[ br ] %= mod;
    }
    
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<=MAXX;j++)
        {
            if( (j & (1<<i)) == 0 )
            {
                uni[j] *= uni[j ^ (1<<i)];
                uni[j] %= mod;
            }
        }
    }
    for(int i=0;i<=MAXX;i++)
    {
        uni[i]--;
    }


    for(int i=0;i<m;i++)
    {
        for(int j=0;j<=MAXX;j++)
        {
            if( (j & (1<<i)) == 0 )
            {
                uni[j] -= uni[j ^ (1<<i)];
                uni[j] += mod;
                uni[j] %= mod;
            }
        }
    }

    for(int i=0;i<=MAXX;i++)
    {
        int bits = __builtin_popcount(i);
        f[bits] += uni[i];
        f[bits] %= mod;
    }
    for(int i=0;i<=m;i++)
    {
        cout<<f[i]<<" ";
    }
    return 0;
}
