/*
We are using the following dp on bitmasks:

  dp[x] = the maximum period of time that the cow can continuously watch movies if she watches only the movies with the corresponding 
          bits active
          
Now, we can just pass through all the states and take the minimum of the bits activated in the states which result in a period >= L.
*/

#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define pb push_back
using namespace std;

int n,l;
int MAX;
int d[21];
vector<int>a[21];

int dp[(1<<20) + 5];
void precalc()
{
    MAX = (1<<n) - 1;
    dp[0] = 0;
    for(int i=1;i<=MAX;i++)
    {
        dp[i] = -1;
        for(int j=0;j<n;j++)
        {
            if( i & (1<<j) )
            {
                int tre = dp[i ^ (1<<j)];

                int sz = a[j].size();
                int levo = 0;
                int desno = sz - 1;
                int sol = -1;
                while(levo<=desno)
                {
                    int mid=(levo+desno)/2;
                    if(a[j][mid] <= tre)
                    {
                        sol = max(sol, mid);
                        levo = mid + 1;
                    }
                    else
                    {
                        desno = mid - 1;
                    }
                }

                if(sol >= 0)
                {
                    dp[i] = max(dp[i], a[j][sol] + d[j]);
                }
            }
        }
    }
}

int main()
{
    ifstream cin("movie.in");
    ofstream cout("movie.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>l;
    for(int i=0;i<n;i++)
    {
        int br;
        cin>>d[i]>>br;
        a[i].resize(br);
        for(int j=0;j<br;j++)
        {
            cin>>a[i][j];
        }
    }

    precalc();

    int sol = n + 5;
    for(int i=0;i<=MAX;i++)
    {
        if(dp[i]>=l)
        {
            sol = min (sol, __builtin_popcount(i));
        }
    }

    if(sol > n)
    {
        sol = -1;
    }

    cout<<sol;
    return 0;
}
