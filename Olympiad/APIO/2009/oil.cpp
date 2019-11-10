/*
  The same as in the editorial.
*/

#include<bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
#define maxn 1505
#define ui unsigned int
using namespace std;

int n,m,k;
ui a[maxn][maxn];
ui sum[maxn][maxn];
ui sk[maxn][maxn];

int compute(int i,int j)
{
    int i2=i+k-1;
    int j2=j+k-1;

    if(i2>n || j2>m)return -1;

    return sum[i2][j2]-sum[i-1][j2]-sum[i2][j-1]+sum[i-1][j-1];
}


ui ul[maxn][maxn],ur[maxn][maxn],dl[maxn][maxn],dr[maxn][maxn];
ui u[maxn],d[maxn],r[maxn],l[maxn];
ui uu[maxn][maxn],ll[maxn][maxn];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            cin>>a[i][j];
        }

    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)sum[i][j]=0;

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
        }
    }

    for(int i=1;i+k-1<=n;i++)
        for(int j=1;j+k-1<=m;j++)
        {
            sk[i][j]=compute(i,j);
        }



    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
        {
            ul[i][j]=0;
            ur[i][i]=0;
            dl[i][j]=0;
            dr[i][j]=0;
        }
    }
    for(int i=k;i<=n;i++)
    {
        for(int j=k;j<=m;j++)
        {
            ul[i][j]=max(ul[i-1][j],ul[i][j-1]);
            ul[i][j]=max(ul[i][j],sk[i-k+1][j-k+1]);
        }
    }
    for(int i=k;i<=n;i++)
    {
        for(int j=m-k+1;j>0;j--)
        {
            ur[i][j]=max(ur[i-1][j],ur[i][j+1]);
            ur[i][j]=max(ur[i][j],sk[i-k+1][j]);
        }
    }
    for(int i=n-k+1;i>0;i--)
    {
        for(int j=k;j<=m;j++)
        {
            dl[i][j]=max(dl[i+1][j],dl[i][j-1]);
            dl[i][j]=max(dl[i][j],sk[i][j-k+1]);
        }
    }
    for(int i=n-k+1;i>0;i--)
    {
        for(int j=m-k+1;j>0;j--)
        {
            dr[i][j]=max(dr[i+1][j],dr[i][j+1]);
            dr[i][j]=max(dr[i][j],sk[i][j]);
        }
    }

    for(int i=0;i<=n;i++)
    {
        u[i]=ul[i][m];
        d[i]=dl[i][m];
    }
    for(int j=0;j<=m;j++)
    {
        l[j]=ul[n][j];
        r[j]=ur[n][j];
    }

    for(int i=k+1;i+k<=n;i++)
    {
        uu[i][i+k-1]=sk[i][1];
        for(int j=1;j+k<=m;j++)uu[i][i+k-1]=max(uu[i][i+k-1], sk[i][j]);
    }
    for(int d=k+1;d+2*k<=n;d++)
    {
        for(int i=k+1;i+d+k<=n;i++)
        {
            uu[i][i+d-1]=max(uu[i][i+d-2],uu[i+1][i+d-1]);
        }
    }

    for(int j=k+1;j+k<=m;j++)
    {
        ll[j][j+k-1]=sk[1][j];
        for(int i=1;i+k<=n;i++)ll[j][j+k-1]=max(ll[j][j+k-1], sk[i][j]);
    }
    for(int d=k+1;d+2*k<=m;d++)
    {
        for(int j=k+1;j+d+k<=m;j++)
        {
            ll[j][j+d-1]=max(ll[j][j+d-2],ll[j+1][j+d-1]);
        }
    }

    ui sol=0;
    for(int i=k;i+k<=n;i++)
    {
        for(int j=k;j+k<=m;j++)
        {
            int presol=sol;
            sol=max(sol, ul[i][j] + dl[i+1][j] + r[j+1]);
            sol=max(sol, l[j] + ur[i][j+1] + dr[i+1][j+1]);
            sol=max(sol, ul[i][j] + ur[i][j+1] + d[i+1]);
            sol=max(sol, u[i] + dl[i+1][j] + dr[i+1][j+1]);
        }
    }

    for(int i=k;i+2*k<=n;i++)
    {
        for(int j=i+1;j+k<=n;j++)
        {
            sol=max(sol, u[i] + uu[i+1][j] + d[j+1]);
        }
    }
    for(int i=k;i+2*k<=m;i++)
    {
        for(int j=i+1;j+k<=m;j++)
        {
            sol=max(sol, l[i] + ll[i+1][j] + r[j+1]);
        }
    }
    cout<<sol<<"\n";
    return 0;
}
