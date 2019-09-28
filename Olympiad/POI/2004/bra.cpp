/**

The idea is to greedily colour each node with 1 (and then with 0) and then while possible make changes. Then when the algorithm terminates
using the colours of each vertex in both cases (colouring with 1 and 0), we can easily get the desired data. So, all it remains to be done
is to prove that the algorithm terminates and that we can really get the desired data about the nodes.

Firstly, we will prove few useful lemmas that can help us prove that the algorithm really terminates. Also, we assume that we are dealing
with the colouring with 1 (in which we firstly colour everything with 1).

Claim 0. Throughout the algorithm the numbers on a fixed node decreases.
  Proof: Suppose that it is not the case. Look at the first time when the algorithm increases the number on some node. It is not hard to
 get a contradiction from there.
  
Corollary 1. The algorithm will eventually terminate.
  Proof: It immediately follows from the previous claim.
  
Claim 2. Let v be a node of our graph and let c be its final colour. Then there is no valid colouring of our graph s.t. the colour of v
is bigger than c.
  Proof: Similarly as Claim 0.
**/
#include<bits/stdc++.h>
#define maxn 10005
using namespace std;

int n;
vector<int>adj[maxn];

int col[maxn][2];
int zb[maxn];


bool ok(int v,int cc)
{
    bool one=(zb[v]>0);
    bool minus_one=(zb[v]<0);
    bool zero=(zb[v]==0);

    return (one && col[v][cc]==1) || (zero && col[v][cc]==0) || (minus_one && col[v][cc]==-1);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=2;i<=n-1;i++)
    {
        int k;
        cin>>k;

        while(k>0)
        {
            int a;
            cin>>a;

            adj[a].push_back(i);
            k--;
        }
    }


    int boja[2]; ///for easier condition checking
    boja[0]=-1; ///represents 0
    boja[1]=1;  ///represents 1


    for(int b=0;b<2;b++)
    {
        for(int i=0;i<n;i++)
        {
            col[i][b]=boja[b];
            zb[i]=0;
        }
        col[0][b]=boja[0];
        col[1][b]=boja[1];

        for(int i=0;i<n;i++)
        {
            for(auto x:adj[i])
            {
                zb[x]+=col[i][b];
            }
        }

        bool t=true;
        while(t)
        {
            t=false;
            for(int i=2;i<n;i++)
            {
                int br=0;
                while(!ok(i,b))
                {
                    t=true;
                    col[i][b]-=boja[b];
                    br++;
                }

                if(br>0)
                {
                    for(auto x:adj[i])
                    {
                        zb[x]-=br*boja[b];
                    }
                }
            }
        }
    }

    for(int i=0;i<n;i++)
    {
        if(col[i][0]==col[i][1])
        {
            if(col[i][0]==1)cout<<"1\n";
            if(col[i][0]==0)cout<<"1/2\n";
            if(col[i][0]==-1)cout<<"0\n";
        }
        else
        {
            cout<<"?\n";
        }
    }
    return 0;
}
