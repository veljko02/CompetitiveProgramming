/**
  So, let's start with all the nodes. Then, by the problem assumption we know that there is a node with deg <=k, let it be v. So, there 
  are 2 options. A clique contains it or it does not contain it. We can easily deal with the first case because deg v <= k, just count
  the number of edges in each subset of neihghbours of v with some dp and preprocessing. And in order to find the largest clique that 
  does not v, we can just apply the same proccess again. So, just delete v and find a node v' with deg v' <= k. Its existence comes from
  the problem assumption. Now, the only problem is finding a node with deg <= k and computing some base cases for dp. However, we can 
  deal with the both things, for the first we only need to use an array of deques mq[50005] such that mq[i] contains all the nodes with 
  deg equal to i. The dp problem can be solved using binary search. 
**/
#include<bits/stdc++.h>
#define maxn 50005
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;

int n,k;
vector<int>adj[maxn];
deque<int>mq[maxn];
bool bio[maxn];
int deg[maxn];

int brbit[2000];
vector<int>bits[2000];
vector<int>v;
int dp[maxn];

int ima(int x,int y) // the aforementioned binary search for dealing with some base cases for dp
{
    int levo = 0;
    int desno = adj[x].size() - 1;
    while(levo<=desno)
    {
        int mid = (levo+desno)/2;
        if(adj[x][mid] == y)return 1;
        if(adj[x][mid] > y)desno = mid - 1;
        else levo = mid + 1;
    }
    return 0;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for(int i=0;i<1500;i++)
    {
        brbit[i] = __builtin_popcount(i);
        for(int j=0;(1<<j)<=i;j++)
        {
            if(i & (1<<j))
            {
                bits[i].pb(j);
            }
        }
    }

    cin>>n>>k;
    for(int i=0;i<n;i++)
    {
        int l;
        cin>>l;
        adj[i].resize(l);
        for(int j=0;j<l;j++)
        {
            cin>>adj[i][j];
        }
        sort(adj[i].begin(),adj[i].end());

        bio[i]=false;
        mq[l].pb(i);
        deg[i]=l;
    }


    int sol = 1;
    int ostalo  = n;
    while(ostalo > 0)
    {
        ostalo --;
        int tre = -1;
        for(int i=0;i<=k;i++)
        {
            while(!mq[i].empty() && (bio[ mq[i].back() ] ||  deg[ mq[i].back() ] != i))
            {
                mq[i].pop_back();
            }
            if(!mq[i].empty())
            {
                tre = mq[i].back();
                break;
            }
        }

        bio[tre] = true;
        v.clear();
        for(auto sus: adj[tre])
        {
            if(!bio[sus])
            {
                deg[sus]--;
                mq[deg[sus]].pb(sus);
                v.pb(sus);
            }
        }

        int sz = v.size();
        for(int i=0;i<(1<<sz);i++)
        {
            dp[i] = 0;
            if(brbit[i] == 2)
            {
                dp[i] = ima(v[bits[i][0]],v[bits[i][1]]);
            }
            else if(brbit[i] >= 3)
            {
                dp[i] = dp[i ^ (1<<bits[i][0])] + dp[i ^ (1<<bits[i][1])] + dp[i ^ (1<<bits[i][2])];
                dp[i] -= dp[i ^ (1<<bits[i][0]) ^ (1<<bits[i][1])];
                dp[i] -= dp[i ^ (1<<bits[i][0]) ^ (1<<bits[i][2])];
                dp[i] -= dp[i ^ (1<<bits[i][2]) ^ (1<<bits[i][1])];
                dp[i] += dp[i ^ (1<<bits[i][0]) ^ (1<<bits[i][1]) ^ (1<<bits[i][2])];
            }

            if(dp[i] == brbit[i] * (brbit[i] - 1)/2)
            {
                sol = max(sol,brbit[i] + 1);
            }
        }
    }

    cout<<sol<<endl;
    return 0;
}
