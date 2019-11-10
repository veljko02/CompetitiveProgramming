/*
    1) Let A be an arbitrary set of dwarfs. Suppose that those dwarfs can all go out. Notice that then it is possible for them to escape
    just by going according to order of their sum of height and length (so just sort them increasingly (comparing the already mentioned 
    sum) and take them in the order we get that way).
    
    2) Sort the dwarfs according to the abovementioned sum. 
    
    3) So, now it is not hard to notice that we can just do some "weird" dp (in sense that it was unexpected in the beginning):
    
    dp[i][k] - means the biggest of the heights of the dwarfs who did not escape among the first i dwarfs if we know that exactly k guys
    escaped among them
    
    The answer is the biggest k such that dp[n][k] is greater than 0.
*/

#include<bits/stdc++.h>
#define maxn 2005
#define ll long long
#define pii pair<int,int>
#define zbir first
#define ind second
#define INF 1000000000
using namespace std;

int n,d;
int h[maxn];
int l[maxn];
pii a[maxn];
int sum[maxn];

int dp[maxn][maxn];
int main()
{
    ifstream cin("pitici3.in");
	  ofstream cout("pitici3.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>h[i]>>l[i];
        a[i].zbir=h[i]+l[i];
        a[i].ind=i;
    }
    cin>>d;
    sort(a+1,a+n+1);

    sum[0]=0;
    for(int i=1;i<=n;i++)
    {
        sum[i] = sum[i-1] + h[ a[i].ind ];
    }
    

    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)dp[i][j]=-INF;

    dp[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i][0] = dp[i-1][0] + h[ a[i].ind ];
        for(int j=1;j<=i;j++)
        {
            dp[i][j]=max(dp[i][j],dp[i-1][j] + h[ a[i].ind ]);
            int visina = sum[n] - sum[i] + dp[i-1][j-1] + a[i].zbir;
            if(visina>=d)
            {
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
            }
        }
    }


    int sol=0;
    for(int i=1;i<=n;i++)
    {
        if(dp[n][i]>=0)
        {
            sol=max(i,sol);
        }
    }
    cout<<sol<<"\n";
    return 0;
}
