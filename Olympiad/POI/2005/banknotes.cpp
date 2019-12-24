/**
  So, we basically do the obvious dp[n][k] but speed it up with deques. When we proccess i-th element we have b[i] deques which save the
  appropriate values of dp[i-1][j] - k/b[j] in ascending order, i.e. w-th deque save those values for j congruent to w mod b[i]. It is
  not hard to update the deques and to compute the dp states in O(n*k) now.
**/

#include <bits/stdc++.h>
#define maxn 205
#define pii pair<int,int>
#define x first
#define y second
#define ll long long
#define MAX 20000
#define INF 20000000
using namespace std;

int n,k;
int b[maxn];
int c[maxn];

int dp[maxn][MAX + 5];
int stigo[maxn][MAX + 5];
deque<int>mq[MAX + 5];

int sol[maxn];
void vrati(int ind,int val)
{
    if(ind == 0) return;
    sol[ind] = (val - stigo[ind][val])/b[ind];
    vrati(ind - 1, stigo[ind][val]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)cin>>c[i];
    cin>>k;

    dp[0][0] = 0;
    for(int i=1;i<=k;i++)
    {
        dp[0][i] = INF + MAX;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<b[i];j++){while(!mq[j].empty())mq[j].pop_back();}
        for(int j=0;j<=k;j++)
        {
            int ost = j % b[i];
            /// DODAVANJE LIKA U DEQUE
            while(!mq[ost].empty())
            {
                int nazad = mq[ost].back();
                if(dp[i-1][nazad] - nazad/b[i] >= dp[i-1][j] - j/b[i])
                {
                    mq[ost].pop_back();
                }
                else
                {
                    break;
                }
            }
            mq[ost].push_back(j);

            while(!mq[ost].empty())
            {
                int tre = mq[ost].front();
                if((j - tre)/b[i] > c[i])
                {
                    mq[ost].pop_front();
                }
                else
                {
                    break;
                }
            }

            int najb = mq[ost].front();
            dp[i][j] = dp[i-1][ najb ] - najb/b[i] + j/b[i];
            stigo[i][j] = najb;
        }
    }

    vrati(n,k);
    cout<<dp[n][k]<<"\n";
    for(int i=1;i<=n;i++)
    {
        cout<<sol[i]<<" ";
    }
    return 0;
}
