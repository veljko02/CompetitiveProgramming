/**
  Same as in the editorial: http://hsin.hr/coci/archive/2007_2008/
**/
#include<bits/stdc++.h>
#define maxn 100005
#define pb push_back
#define ll long long
#define INF 1000000000000000
using namespace std;

int n;
ll a[maxn];
ll b[maxn];

ll dp[maxn];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i]>>b[i];

    sort(a+1,a+n+1);
    sort(b+1,b+n+1);

    dp[0] = 0;
    for(int i=1;i<=n;i++)
    {
        dp[i] = INF;
        if(i>=1 && a[i]!=b[i])
        {
            dp[i] = min(dp[i], dp[i-1] + abs(a[i] - b[i]));
        }
        if(i>=2 && a[i]!=b[i-1] && a[i-1]!=b[i])
        {
            dp[i] = min(dp[i], dp[i-2] + abs(a[i] - b[i-1]) + abs(a[i-1] - b[i]));
        }
        if(i>=3)
        {
            ll minn = INF;
            for(int p1=0;p1<=2;p1++)
            {
                for(int p2=0;p2<=2;p2++)
                {
                    if(p2==p1)continue;
                    for(int p3=0;p3<=2;p3++)
                    {
                        if(p1==p3 || p2==p3)continue;
                        if(a[i-2]==b[i-p1] || a[i-1]==b[i-p2] || a[i]==b[i-p3])continue;
                        ll tre = abs(a[i-2] - b[i-p1]) + abs(a[i-1] - b[i-p2]) + abs(a[i] - b[i-p3]);
                        minn = min(minn, tre);
                    }
                }
            }
            dp[i] = min(dp[i], dp[i-3] + minn);
        }
    }

    cout<<dp[n]<<"\n";
    return 0;
}
