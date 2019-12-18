/**
dp[x][br] = the number of the given integers that differ from x in exactly br bits

It is not hard to derive a recurrent formula on a paper now. We just have to fix one bit and that is going to be chnaged and then
using one of the already computed states with br-1 instead of br. However, there will be a few numbers we have counted too many times 
and some which we shouldn't count (which differ from x in br-2 bits), but we can easily deal with those cases too.
**/

#include <bits/stdc++.h>
#define MAX (1<<20) - 1
#define MAXBIT 20
#define maxn 100005
#define ll long long
#define pii pair<int,int>
using namespace std;

int n;
int a[maxn];
int dp[MAX][5];
int cnt[MAX][5];

int main()
{
    ifstream cin("aiacubiti.in");
    ofstream cout("aiacubiti.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        dp[a[i]][0]++;
    }

    for(int br=1;br<=4;br++)
    {
        for(int i=0;i<=MAX;i++)
        {
            dp[i][br] = 0;
            for(int j=0;j<MAXBIT;j++)
            {
                dp[i][br] += dp[i ^ (1<<j)][br-1];
            }
            if(br!=1)
            {
                dp[i][br] -= (MAXBIT - (br-2)) * dp[i][br-2];
            }
            dp[i][br] /= br;
        }
    }

    ll sol = 0;
    for(int i=0;i<n;i++)
    {
        sol += dp[a[i]][4];
    }
    cout<<sol/2<<endl;
    return 0;
}
