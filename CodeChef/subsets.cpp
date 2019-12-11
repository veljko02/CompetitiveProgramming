#include <bits/stdc++.h>
#define maxn (1<<20) + 5
#define mod 1000000007
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;

/** Firstly, notice that we basically have a graph with n nodes and we want to find the number of its complete subgraphs. It is natural 
to try some meet in the middle, so let's divide the nodes into two halves. Now, we can easily compute for each subset of both halves
whether the resulting subgraph is complete in O(n*2^(n/2)). Now, it is quite natural to try to fix a subset from the first half and count
how many subsets of the second half give a complete subgraph. In order to do so, we can firstly take care of edges between the two halves.
We can do that just by passing over all the nodes in the second half and checking whether it is connected to all of the chosen nodes
in the already fixed subset of the first half. Then all it remains for us to do is to check how many subsets of those vertices in the 
second half are complete in fact and we can do that by SOS dp in O(n*2^(n/2)).

REMARK: We can check whether there is an edge between two nodes by checking whether their product is divisible by some prime number up to
the third root of it.

**/

int n;
ll a[42];
bool adj[42][42];
int pr_sz;
vector<ll>primes;
const int MAX = 250000;
bool prost[MAX + 5];

void sieve()
{
    for(int i=2;i<=MAX;i++)prost[i]=true;
    for(int i=2;i<=MAX;i++)
    {
        if(prost[i])
        {
            primes.pb(i);
            for(int j = 2*i;j<=MAX;j+=i)
            {
                prost[j]=false;
            }
        }
    }
}
bool moze(ll x)
{
    for(int i=0;i<pr_sz;i++)
    {
        ll br = primes[i];
        ll pp = br*br*br;
        if(pp>x)break;
        if(x%pp==0)
        {
            return false;
        }
    }
    return true;
}

int br[(1<<21) + 5][2];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    sieve();
    pr_sz=primes.size();

    int query;
    cin>>query;
    while(query>0)
    {
        query--;
        cin>>n;
        for(int i=0;i<=n-1;i++)
        {
            cin>>a[i];
        }
        for(int i=0;i<=n-1;i++)
        {
            for(int j=i+1;j<=n-1;j++)
            {
                adj[i][j]=moze(a[i]*a[j]);
                adj[j][i]=moze(a[i]*a[j]);
            }
        }

        int poc[2],kraj[2];
        poc[0]=0;
        kraj[0]=(n-1)/2;
        poc[1]=kraj[0]+1;
        kraj[1]=n-1;
        int duz[2];
        for(int t=0;t<2;t++)
        {
            duz[t] = kraj[t]-poc[t]+1;
            for(int i=0;i<(1<<duz[t]);i++)
            {
                br[i][t] = 1;
                int bitovi[2];
                if(__builtin_popcount(i) > 1)
                {
                    int dosad=0;
                    br[i][t] = 1;
                    for(int j=0;j<duz[t] && dosad<2;j++)
                    {
                        if(i & (1<<j))
                        {
                            bitovi[dosad] = j;
                            br[i][t] &= br[i ^ (1<<j)][t];
                            dosad++;
                        }
                    }
                    br[i][t] &= adj[ bitovi[0] + poc[t] ][ bitovi[1] + poc[t] ];
                }
            }
        }


        int MAXX = (1<<duz[1]) - 1;
        for(int i=0;i<duz[1];i++)
        {
            for(int j=0;j<=MAXX;j++)
            {
                if(j & (1<<i))
                {
                    br[j][1] += br[j ^ (1<<i)][1];
                }
            }
        }
        
        
        ll sol=0;
        vector<int>v;
        for(int i=0;i<(1<<duz[0]);i++)
        {
            if(!br[i][0])continue;
            v.clear();
            for(int j=0;j<duz[0];j++)
            {
                if(i & (1<<j))
                {
                    v.pb(j);
                }
            }

            int tre=0;
            for(int j=poc[1];j<=kraj[1];j++)
            {
                bool t=true;
                for(auto x:v)
                {
                    if(!adj[x][j])t=false;
                }
                if(t)
                {
                    tre += 1<<(j-poc[1]);
                }
            }



            sol+=br[tre][1];
        }

        cout<<sol<<endl;
    }
    return 0;
}
