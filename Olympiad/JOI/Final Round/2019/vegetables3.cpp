/**
https://github.com/luciocf/Problems/blob/master/JOI/Final%20Round/Final%20Round%202019/vegetables3.cpp
**/

#include<bits/stdc++.h>
#define INF 100000000
#define maxn 405
using namespace std;

map<char,int>br;
int n;
string s;
int dp[maxn][maxn][maxn][3];
int col[maxn][3];
int tot[3];
int num[maxn][3];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    br['R']=0;
    br['G']=1;
    br['Y']=2;

    cin>>n;
    cin>>s;

    tot[0]=tot[1]=tot[2]=0;
    for(int i=0;i<n;i++)
    {
        int boja=br[s[i]];
        tot[boja]++;
        col[tot[boja]][boja]=i;

        if(i==0)
        {
            for(int j=0;j<=2;j++)
            {
                num[i][j]=0;
            }
        }
        else
        {
            for(int j=0;j<=2;j++)
            {
                num[i][j]=num[i-1][j];
            }
        }
        num[i][boja]++;
    }



    int red[3];
    for(red[0]=0;red[0]<=tot[0];red[0]++)
    {
        for(red[1]=0;red[1]<=tot[1];red[1]++)
        {
            for(red[2]=0;red[2]<=tot[2];red[2]++)
            {
                for(int i=0;i<=2;i++)
                {
                    dp[ red[0] ][ red[1] ][ red[2] ][i]=INF;
                    if(red[i]==0)continue;

                    int tre[3];
                    for(int j=0;j<=2;j++)
                    {
                        tre[j]=red[j];
                    }
                    tre[i]--;


                    int pre_poz=col[red[i]][i];
                    int left_ok=0;
                    for(int j=0;j<=2;j++)
                    {
                        int broj=0;
                        if(pre_poz!=0)
                        {
                            broj=num[pre_poz-1][j];
                        }
                        left_ok+=min(tre[j],broj);
                    }


                    int poz=red[0]+red[1]+red[2]-1;
                    int dod= (pre_poz+poz) - 2*left_ok;
                    int ost1=(i+1)%3;
                    int ost2=(i+2)%3;
                    if(poz==0)
                    {
                        dp[ red[0] ][ red[1] ][ red[2] ][i]=dod;
                        continue;
                    }


                    dp[ red[0] ][ red[1] ][ red[2] ][i]=min(dp[ red[0] ][ red[1] ][ red[2] ][i], dp[ tre[0] ][ tre[1] ][ tre[2] ][ost1] + dod);
                    dp[ red[0] ][ red[1] ][ red[2] ][i]=min(dp[ red[0] ][ red[1] ][ red[2] ][i], dp[ tre[0] ][ tre[1] ][ tre[2] ][ost2] + dod);
                }
            }
        }
    }

    int sol=INF;
    for(int i=0;i<=2;i++)
    {
        sol=min(sol,dp[ tot[0] ][ tot[1] ][ tot[2] ][i]);
    }

    if(sol>=INF)cout<<"-1"<<endl;
    else
    {
        sol/=2;
        cout<<sol<<endl;
    }

    return 0;
}
