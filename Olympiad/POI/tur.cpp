/**
The solution is based on the following few observations:

1) There is a node v with in_deg(v)+out_deg(v)<=2*m/n
  Proof:
   - It is a very basic fact about graphs, we can just suppose the contrary and immediately get contradiction.
   
2) Let W,L be the sets of the winning and losing programmes, respectively. Then for any w in W and l in L, there is an edge from w to l.
  Proof:
   - We can just suppose the contrary and it is not hard to get contradiction.
   
3) It is possible to check whether a particular programme v is winning in O(m + in_deg(v)^2)
  Proof:
   
   - Define the 'good' programmes in the following recursive way:
      * DEFINITION: Our starting vertex v is 'good'. A vertex u is 'good' if there is a 'good' vertex x s.t. x can defeat u.
   - Let's say that a vertex is 'bad' iff it is not 'good'.
   - Let B, G denote the sets of 'bad' and 'good' vertices, respectively. It is obvious that there for each b in B and g in G, there is 
   an edge from b to g (this statement resembles the second observation).
   - v is winning iff |B|=0
   - It is obvious that the only candidates for 'bad' nodes are the all the vertices from which there is an edge to v. Let's call the set
   of those nodes B' and let G' be its complement.   
   - Now, let's do the following:
    
    * Repeatedly go through B'. Let's say that we are currently looking at v in B'.
    * If there is a node u in G' s.t. there is no edge from v to u, then v is B.
    * If there is no such for any v in B', then stop.
    
   - We claim that the final B' is in fact B and the final G' is in fact G. 
   Proof:
    Suppose the contrary. It is obvious that G' is a subset of G at every moment. So, our assertion does not hold (we supposed so), we 
    know that there is a 'good' node u in B'. Notice that there is a path (if there is no edge between some nodes a,b then we say
    that ther is a bidirectional edge between them) from v to u using only 'good' vertices. It is not hard to notice that for each
    b' in B' and g' in G', there is an edge from b' to g'. So, if we take the first node in B' on our path, we immediately get contradiction.
    
   - So, we just have to check whether |B'|=0 (or |G'|=n) in order to see whether v is a winning programme.
   NOTE: One way of implementing the above algorithm is to keep track of the number of edges from v to G' for each v in B'.
   
 
So, we are doing the following:

1) Find a node v that satisfies in_deg(v)+out_deg(v)<=2*m/n
2) Check whether it is a winning programme ((2*m/n)^2 is small within the given constraints)
3) Now there are two cases:
   3.1) v is a losing programme
    - Then, we can just run the algorithm for checking whether a node is winning (on all the nodes from which an edge comes to v, observation 2)
   3.2) v is a winning programme
    - Then, in fact we can do the same, but I decided to do modified version of testing whether a node is winning.

NOTE: I somehow overlooked the fact that this algorithm is a bit slower than it was allowed (but it is probably rather hard to create a
test for which it is slower than allowed). However, it passed all the tests.
**/
#include<bits/stdc++.h>
#define maxn 100005
#define ll long long
#define pll pair<ll,ll>
#define pii pair<int,int>
using namespace std;

int n[2];
vector<int>in[maxn][2];
vector<int>out[maxn][2];

bool sig[maxn];
int szpob;
int outpob[maxn];

vector<int>nodes[2];
bool winner(int v,int graph)
{
    szpob=0;
    for(auto i:nodes[graph])
    {
        outpob[i]=0;
        sig[i]=true;
    }
    for(auto x:in[v][graph])
    {
        sig[x]=false;
    }
    for(auto i:nodes[graph])
    {
        if(sig[i])
        {
           szpob++;
           for(auto x:in[i][graph])
           {
               outpob[x]++;
           }
        }
    }
    bool t=true;
    while(t)
    {
        t=false;
        for(auto x:in[v][graph])
        {
            if(!sig[x] && outpob[x]!=szpob)
            {
                t=true;
                szpob++;
                sig[x]=true;

                for(auto u:in[x][graph])
                {
                    outpob[u]++;
                }
            }
        }
    }

    return (szpob==n[graph]);
}


bool cer[maxn];
vector<int>win;
vector<int>lose;
int inw[maxn];

bool in_in[maxn];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n[0];
    for(int i=1;i<=n[0];i++)
    {
        nodes[0].push_back(i);
        int k;
        cin>>k;
        while(k)
        {
            k--;

            int u;
            cin>>u;
            in[u][0].push_back(i);
            out[i][0].push_back(u);
        }
    }


    int start=1;
    for(int i=1;i<=n[0];i++)
    {
        int tre=in[i][0].size()+out[i][0].size();
        int minn=in[start][0].size()+out[start][0].size();
        if(tre<minn)
        {
            start=i;
        }
    }


    if(winner(start,0))
    {
        for(int i=1;i<=n[0];i++)
        {
            cer[i]=true;
            inw[i]=0;
        }
        for(auto x:out[start][0])
        {
            cer[x]=false;
        }
        for(int i=1;i<=n[0];i++)
        {
            if(cer[i])
            {
                win.push_back(i);
                for(auto x:out[i][0])
                {
                    inw[x]++;
                }
            }
            else
            {
                lose.push_back(i);
            }
        }


        bool t=true;
        while(t)
        {
            t=false;
            for(auto x:lose)
            {
                if(!cer[x] && inw[x]!=win.size())
                {
                    t=true;
                    cer[x]=true;
                    win.push_back(x);

                    for(auto u:out[x][0])
                    {
                        inw[u]++;
                    }
                }
            }
        }
    }


    else
    {
        for(auto x:in[start][0])
        {
            nodes[1].push_back(x);
            in_in[x]=true;
        }

        for(auto x:in[start][0])
        {
            for(auto u:in[x][0])
            {
                if(in_in[u])
                {
                    in[x][1].push_back(u);
                }
            }
            for(auto u:out[x][0])
            {
                if(in_in[u])
                {
                    out[x][1].push_back(u);
                }
            }
        }

        n[1]=in[start][0].size();
        for(auto x:in[start][0])
        {
            if(winner(x,1))
            {
                win.push_back(x);
            }
        }
    }

    sort(win.begin(),win.end());
    cout<<win.size()<<" ";
    for(auto x:win)cout<<x<<" ";

    return 0;
}
