/**
  dp[v][s] = the minimum price we have to pay if we build s sawmills in the subtree of v in total and if we build a sawmill in v
  So, how do we compute all the dp states of v if we know them for each vertex in its subtree?
     - The key is to make "intervals" from each dp value of subtree's vertices and then to do an obvious array cover dp.
     - So, from each dp[w][s] where w is in subtree of v we make an interval in the following way:
          1) We set left border to be the leftmost leaf in subtree of w (in dfs-order) and similarly for the right border
          2) We set s to be the number of already built sawmills in that interval (I used "taken" for some reason in the code)
          3) We want the price of the interval to be the the minimum amount of money we will pay if there is no sawmill among the 
          ancestors of w before v. I mean we assign a few consecutive edges in the "ancestors path" to each node (such that there is 
          no edge which is assigned to 2 nodes) and then just compute the minimum amount of money we need to transport all the trees 
          produced in the subtree + the nodes of corresponding edges except the oldest one, to v. Btw, I know it is a bit vague 
          explanation, but it is hard to explain it, it is a bit weird idea. Basically, for each node in the subtree we have a strange 
          structure like subtree + a part of the root's "ancestor's path", and we want to compute the minimum price to transport all
          the produced trees in that structure to the nearest sawmill, i.e. the sum of corresponding dp state and the price needed to
          transport the trees from the "tail" of the structure to the very root.
          Also, we choose the "tail" according to the dfs-order, so that a node covers an edge uv iff the leftmost leaf that is
          covered by u is the same as the leftmost node covered by v.
  complexity: O((nk)^2) 
**/


#include<bits/stdc++.h>
#define maxn 105
#define ll long long
#define pii pair<int,int>
#define pb push_back
#define len second
#define node first
#define INF 20000000007800
using namespace std;

int n,k;
int w[maxn];
int d[maxn];
int p[maxn];
int l[maxn];
int r[maxn];
vector<pii>adj[maxn];
int num_leaf;
vector<int>leaves;

void dfs(int v)
{
    if(adj[v].size()==0)
    {
        //cout<<v<<" ";
        l[v] = leaves.size();
        r[v] = leaves.size();
        leaves.pb(v);
        return;
    }
    l[v] = n+1;
    r[v] = -1;
    for(auto nxt:adj[v])
    {
        dfs(nxt.node);
        l[v] = min(l[nxt.node],l[v]);
        r[v] = max(r[nxt.node],r[v]);
    }
}

struct interval
{
    int left,taken;
    ll price;
};

ll dp[maxn][55];
vector<interval>sus[105];
void add(int v,ll curr_price, int curr_len)
{
    interval www;
    www.left = l[v];
    www.price = curr_price;
    for(int i=1;i<=k;i++)
    {
        www.taken = i;
        www.price += dp[v][i];
        sus[r[v]].pb(www);
        www.price -= dp[v][i];
    }
    if(adj[v].size()==0)
    {
        www.price += curr_len * w[v];
        www.taken  = 0;
        sus[r[v]].pb(www);
        return;
    }

    for(auto nxt:adj[v])
    {
        if(l[nxt.node]!=l[v])add(nxt.node, 0, curr_len + nxt.len);
        else add(nxt.node, curr_price +  w[v] * curr_len, curr_len + nxt.len);
    }
}
ll pom_dp[maxn][55];
void compute(int v)
{
    if(adj[v].size() == 0)return;

    for(auto nxt:adj[v])
    {
        compute(nxt.node);
    }
    for(int i=l[v];i<=r[v];i++)sus[i].clear();
    for(auto nxt:adj[v])
    {
        add(nxt.node,0,nxt.len);
    }

    for(int i=l[v];i<=r[v];i++)
    {
        for(int j=0;j<=k;j++)
        {
            pom_dp[i][j] = INF;
            for(auto x:sus[i])
            {
                if(x.left - 1 < l[v] && x.taken == j)
                {
                    pom_dp[i][j] = min(pom_dp[i][j], x.price);
                }
                else if(x.left - 1 >= l[v] && x.taken <= j)
                {
                    pom_dp[i][j] = min(pom_dp[i][j], pom_dp[x.left - 1][j - x.taken] + x.price);
                }
            }
        }
    }

    for(int j=0;j<=k;j++)
    {
        dp[v][j + 1] = pom_dp[r[v]][j];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>w[i]>>p[i]>>d[i];
        adj[p[i]].pb({i,d[i]});
    }
    dfs(0);//cout<<endl;
    compute(0);

    cout<<dp[0][k + 1]<<endl;
    return 0;
}
