/**
  We are doing the following dp:
  
    dp[i][j][minn][maxx] = the longest increasing subsequence made of a[i,...,j] such that the first element is >= minn 
                           and the last is <= maxx
                           
  It is not hard to compute a state from the previous once, but it is easy to make a mistake.
**/

#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define pb push_back
#define x first
#define y second
#define vek second
using namespace std;

#define maxn 52
#define MIN 1
#define MAX 50
int n;
int a[maxn];
int dp[maxn][maxn][MAX + 3][MAX + 3];

void solve()
{
    for(int d=1;d<=n;d++)
    {
        for(int poc=1;poc+d-1<=n;poc++)
        {
            int kraj=poc+d-1;
            for(int minn=MIN;minn<=MAX;minn++)
            {
                for(int maxx=minn;maxx<=MAX;maxx++)
                {
                    dp[poc][kraj][minn][maxx] = 0;
                    if(d == 1)
                    {
                        if(minn <= a[poc] && a[poc] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = 1;
                        }
                    }
                    else if(d == 2)
                    {
                        if(minn <= a[poc] && a[poc] <= maxx   &&   minn <= a[kraj] && a[kraj] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = 2;
                        }
                        else if(minn <= a[poc] && a[poc] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = 1;
                        }
                        else if(minn <= a[kraj] && a[kraj] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = 1;
                        }
                    }
                    else
                    {
                        dp[poc][kraj][minn][maxx] = dp[poc + 1][kraj - 1][minn][maxx];
                        dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc][kraj-1][minn][maxx]);
                        dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj][minn][maxx]);
                        if(minn <= a[poc] && a[poc] <= maxx   &&   minn <= a[kraj] && a[kraj] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj-1][min(a[poc],a[kraj])][max(a[poc],a[kraj])] + 2);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj][a[poc]][maxx] + 1);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc][kraj-1][minn][a[kraj]] + 1);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj-1][minn][a[poc]] + 1);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj-1][a[kraj]][maxx] + 1);
                        }
                        else if(minn <= a[poc] && a[poc] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj-1][minn][a[poc]] + 1);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj][a[poc]][maxx] + 1);
                        }
                        else if(minn <= a[kraj] && a[kraj] <= maxx)
                        {
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc][kraj-1][minn][a[kraj]] + 1);
                            dp[poc][kraj][minn][maxx] = max(dp[poc][kraj][minn][maxx], dp[poc+1][kraj-1][a[kraj]][maxx] + 1);
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    ifstream cin("subrev.in");
    ofstream cout("subrev.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    solve();
    cout<<dp[1][n][MIN][MAX]<<endl;
    return 0;
}
