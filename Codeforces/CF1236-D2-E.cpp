/**
  Firstly notice that if we can go from position x to position y than there is a scenario such that we start at x and end at y. So, all 
  we have to do is to compute the furthest left (right) position we can reach from each starting position. We will only deal with the 
  rigthmost position since it is the same for the leftmost. It will be too slow to do that separately for each position (O(n*m)), so 
  let's try to do it for all positions simultaneously. Let S_1,i; S_2,i; ...; S_n,i (1<=i<=m+1) be sets such that S_j,i contain all 
  the indices k such that the rigthmost position that is reachable from k after i-th obstacle is j. So, how does S_1,i; S_2,i; ... S_n,i 
  differ from S_1,i+1; S_2,i+1; ... S_n,i+1? Unfortunately, all of them change, but only two of them does not just shift to right for 1 
  position. So, let's use that thing. We will alter our definition of S_i,j in order to make it easier to deal with them. Let S_i,j 
  represent the set of all indices k such that the rightmost position of k after i-th obstacle is j + i. Now, the magic has happened 
  and only two of our sets change at each obstacle. Precisely S_i,a[i]-i and S_i,a[i]-i- 1. So, we have:
    
                        S_i,a[i]-i = the empty set
                      S_i,a[i]-i-1 = S_i-1,a[i]-i union S_i-1,a[i]-i-1
                    
  Now, there are a few approaches, for example segment tree, dsu etc. We will go with dsu.
  So, basically we have n sets S_1, S_2, ..., S_n and at each step we can choose a set S_i and do the following:
  
                        S_i = the empty set
                      S_i-1 = S_i-2 union S_i-1
                      
  Since we know all the updates in the advance we can approach it offline. So, we construct n + 2*m (m is in fact the number of updates)
  sets. Each of them represents some S_i, 1<=i<=n in some moment. To be precise, S_n + 2*i - 1 represents S_a[i]-1 after the i-th
  obstacle and S_n + 2*i represents S_a[i] = the empty set, after the i-th obstacle. So for each index 1<=k<=n we keep the latest set
  that has the corresponding data (posl[k]). Also for each set we keep what its type is (which S_i, 1<=i<=n it represents). So, let's say
  that we currently deal with the i-th obstacle. We can just set n + 2*i - 1 to be the parent of posl[a[i] - i] and posl[a[i] - i - 1].
  We also appropriately update posl array. At the end we just have to see what the furthest descedant of k for each 1<=k<=n, is and see
  what its type is, then we can easily compute the desired right bound and get the solution.
**/
#include<bits/stdc++.h>
#define maxn 100005
#define INF (int)(1e9 + 77)
#define ll long long
using namespace std;

int n,m;
int a[maxn];
int p[5 * maxn + 100];

int par(int v)
{
    if(v==p[v])return v;
    return p[v] = par(p[v]);
}


int posl[3 * maxn + 100];
int cuva[5 * maxn + 100];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin>>n>>m;

	if(n==1)
    {
        cout<<"0\n";
        return 0;
    }
	int dod = m + 5;
	int sz = n + 2*dod;
	int sets = sz + 2*m;

	for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        a[i] += dod;
    }

	ll sol = -n;
	for(int i=1;i<=sets;i++)
    {
        if(i<=sz)
        {
            cuva[i] = i;
            posl[i] = i;
        }
        p[i] = i;
    }
    for(int i=1;i<=m;i++)
    {
        int tre = a[i] + i;
        p[ posl[tre] ] = sz + 2*i - 1;
        p[ posl[tre + 1] ] = sz + 2*i - 1;
        posl[tre] = sz + 2*i;
        posl[tre + 1] = sz + 2*i - 1;
        cuva[sz + 2*i] = tre;
        cuva[sz + 2*i - 1] = tre + 1;
    }
    for(int i=1+dod;i<=n+dod;i++)
    {
        int doso = cuva[par(i)] - (m+1);
        sol += i - max(1+dod, doso) + 1;
    }

    for(int i=1;i<=sets;i++)
    {
        if(i<=sz)
        {
            cuva[i] = i;
            posl[i] = i;
        }
        p[i] = i;
    }
    for(int i=1;i<=m;i++)
    {
        int tre = a[i] - i;
        p[ posl[tre] ] = sz + 2*i - 1;
        p[ posl[tre - 1] ] = sz + 2*i - 1;
        posl[tre] = sz + 2*i;
        posl[tre - 1] = sz + 2*i - 1;
        cuva[sz + 2*i] = tre;
        cuva[sz + 2*i - 1] = tre - 1;
    }
    for(int i=1+dod;i<=n+dod;i++)
    {
        int doso = cuva[par(i)] + (m+1);
        sol += min(n+dod, doso) - i + 1;
    }

    cout<<sol<<endl;
	return 0;
}
