/**
  The key thing is that the last cow eats only one pie. Otherwise, we would be able to get more weight.
  Now, it is easy to procceed by range dp.
**/
#include<bits/stdc++.h>
#define maxn 100005
#define INF (int)(1e9 + 77)
#define ll long long
using namespace std;

int n,m;
int dp[305][305];
int maxx[305][305][305];
int w[305][305];
int main()
{
  ifstream cin("pieaters.in");
  ofstream cout("pieaters.out");
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin>>n>>m;
	for(int i=0;i<m;i++)
    {
        int l,r,tez;
        cin>>tez>>l>>r;
        w[l][r] = tez;
    }

    for(int d=1;d<=n;d++)
    {
        for(int i=1;i+d-1<=n;i++)
        {
            int j = i + d - 1;
            for(int k=i;k<=j;k++)
            {
                if(i == j)
                {
                    maxx[k][i][j] = w[i][j];
                }
                else
                {
                    maxx[k][i][j] = w[i][j];
                    if(k != j)
                    {
                        maxx[k][i][j] = max(maxx[k][i][j], maxx[k][i][j-1]);
                    }
                    if(k != i)
                    {
                        maxx[k][i][j] = max(maxx[k][i][j], maxx[k][i+1][j]);
                    }
                }
            }
        }
    }
    for(int d=1;d<=n;d++)
    {
        for(int i=1;i+d-1<=n;i++)
        {
            int j = i + d - 1;
            for(int k=i;k<=j;k++)
            {
                int tre = maxx[k][i][j];
                if(k!=i)tre += dp[i][k-1];
                if(k!=j)tre += dp[k+1][j];
                dp[i][j] = max(dp[i][j], tre);
            }
        }
    }

    cout<<dp[1][n]<<endl;
	return 0;
}
