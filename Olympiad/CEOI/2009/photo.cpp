/**
  Similar to the official solution.
**/
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define maxn 105
#define maxh 200005
#define x first
#define y second
#define INF 200055
#define pb push_back
using namespace std;

int n,a;
pii dot[maxn];
int nxt[INF+500];
set<int>ms;
vector<int>svi_y;

int poc[maxn][maxn][maxn];
int kraj[maxn][maxn][maxn];
int dp[maxn][maxn][maxn];
int resi(int l,int r,int curr_y)
{
    if(l<1 || l>n || r<1 || r>n || l>r || curr_y==INF)return 0;
    if(dp[l][r][curr_y]<=n)return dp[l][r][curr_y];

    for(int i=l;i<=r;i++)
    {
        if(dot[i].x==dot[l].x)
        {
            int desno=resi( poc[i+1][r][curr_y], kraj[i+1][r][curr_y], curr_y);
            dp[l][r][curr_y]=min(dp[l][r][curr_y],1+desno);
            continue;
        }
        int max_y=a/(dot[i].x-dot[l].x);
        if(max_y<dot[l].y)break;

        int levo=resi( poc[l][i][nxt[max_y]], kraj[l][i][nxt[max_y]], nxt[max_y]);
        int desno=resi( poc[i+1][r][curr_y], kraj[i+1][r][curr_y], curr_y);

        dp[l][r][curr_y]=min(dp[l][r][curr_y],levo+desno+1);
    }

    return dp[l][r][curr_y];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>a;
    for(int i=1;i<=n;i++)
    {
        cin>>dot[i].x>>dot[i].y;
    }
    sort(dot+1,dot+1+n);

    ms.insert(1);
    ms.insert(a+10);
    for(int i=1;i<=n;i++)ms.insert(dot[i].y);
    for(auto w:ms)svi_y.pb(w);
    sort(svi_y.begin(),svi_y.end());
    int sz=svi_y.size();
    for(int i=0;i<sz-1;i++)
    {
        for(int j=svi_y[i];j<svi_y[i+1];j++)
        {
            nxt[j]=i+1;
        }
    }

    for(int l=1;l<=n;l++)
    {
        for(int r=l;r<=n;r++)
        {
            for(int i=0;i<sz;i++)
            {
                dp[l][r][i]=n+100;

                kraj[l][r][i]=-100;
                poc[l][r][i]=n+100;
                for(int j=l;j<=r;j++)
                {
                    if(dot[j].y>=svi_y[i])
                    {
                        kraj[l][r][i]=max(kraj[l][r][i],j);
                        poc[l][r][i]=min(poc[l][r][i],j);
                    }
                }
            }
        }
    }


    cout<<resi(1,n,0);
    return 0;
}
