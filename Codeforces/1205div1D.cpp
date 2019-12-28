/**
  My idea was to firstly try for a star tree. One can easily come up with a numbering that covers approximately first n^2/4 numbers 
  and then by finding a centroid it can easily be generalized.
**/

#include<bits/stdc++.h>
#define maxn 100005
#define mod 998244353
#define ll long long
#define pii pair<int,int>
#define pb push_back
#define x second
#define y first
#define INF 20000000007800
using namespace std;

int n;
vector<int>adj[maxn];
int s = -1,par;

int subsz[maxn];
bool centroid(int v,int p)
{
    for(auto x:adj[v])
    {
        if(x == p)continue;
        if(subsz[x] > (n+1)/2)return false;
    }
    return n - subsz[v] <= (n+1)/2;
}
void dfs(int v,int p)
{
    subsz[v] = 1;
    for(auto nxt: adj[v])
    {
        if(nxt==p)continue;
        dfs(nxt,v);
        subsz[v] += subsz[nxt];
    }
    if(s==-1 && centroid(v,p))
    {
        s = v;
    }
}

struct edge
{
    int cv1,cv2,val;
};

vector<edge>sol;
vector<int>vec[2];
bool sus[maxn];
int treba[maxn];
int br[maxn];
int preso;
void dfs2(int v,int p,int type)
{
    if(v!=s)
    {
        br[v] = vec[type][preso];
        preso++;

        edge res;
        res.cv1 = v;
        res.cv2 = p;
        res.val = br[v] - br[p];
        sol.pb(res);
    }
    else
    {
        br[v] = 0;
    }

    for(auto nxt:adj[v])
    {
        if(nxt == p)continue;
        if(sus[nxt] && treba[nxt]!=type)continue;

        dfs2(nxt,v,type);
    }
}

bool cmp(int levo,int desno)
{
    if(subsz[levo] != subsz[desno])return subsz[levo] < subsz[desno];
    return levo < desno;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    if(n==1)return 0;
    if(n==2)
    {
        cout<<"1 2 1\n";
        return 0;
    }
    for(int i=1;i<n;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1,1);
    dfs(s,s);

    for(auto x:adj[s])sus[x] = true;
    sort(adj[s].begin(),adj[s].end(),cmp);
    int sz = adj[s].size();

    int curr_val = subsz[adj[s][sz - 1]];
    treba[adj[s][sz - 1]] = 1;
    int curr_ind = 0;
    while(curr_val < n/3)
    {
        curr_val += subsz[adj[s][curr_ind]];
        treba[adj[s][curr_ind]] = 1;
        curr_ind ++;
    }


    for(int i=1;i<=curr_val;i++)vec[1].pb(i);
    int tre = curr_val + 1;
    for(int i=1;i<=n - curr_val - 1;i++)
    {
        vec[0].pb(tre);
        tre += curr_val + 1;
    }

    preso = 0;
    dfs2(s,s,1);

    preso = 0;
    dfs2(s,s,0);


    for(auto x:sol)
    {
        cout<<x.cv1<<" "<<x.cv2<<" "<<x.val<<"\n";
    }
    return 0;
}
 
