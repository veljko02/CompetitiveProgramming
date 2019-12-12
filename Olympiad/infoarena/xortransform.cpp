/**
So, firstly after playing with numbers on paper one can find that after applying the transform k times we get the xorsum of all numbers
that are on the positions i,j s.t.  (i | j) & k = (i | j). In fact, it is not hard to prove it by induction, just firstly prove that
for k = 2^n it is the xorsum of all a[i][j] s.t. 0 <= i,j < k, and then for other k it easily follows. 
Now, we can just compute the answer for k < 2^22 using SOS dp. There, it appears (2^22) - 1 due to the fact that 2^22 is the first 
power of 2 greater than n*m. It only remains to deal with the case k > 2^22, but it is not hard to notice that then the answer 
would be the same as for k & ((2^22) - 1). 
**/

#include <bits/stdc++.h>
#define maxn 2500005
#define mod 1000000007
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;


int n,m;
vector<int>a[maxn];
const int MAX = (1<<22) - 1;
int dp[MAX + 5];

bool in(int x,int y)
{
    return x>=0 && x<n && y>=0 && y<m;
}
int broj(int x,int y)
{
    if(in(x,y))return a[x][y];
    return 0;
}
void precalc()
{
    for(int i=0;i<=MAX;i++)dp[i]=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            dp[i | j] ^= a[i][j];
        }
    }

    for(int i=0;i<22;i++)
    {
        for(int j=0;j<=MAX;j++)
        {
            if(j & (1<<i))
            {
                dp[j] ^= dp[j ^ (1<<i)];
            }
        }
    }
}

int main()
{
    ifstream cin("xortransform.in");
	  ofstream cout("xortransform.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int query;
    cin>>n>>m>>query;
    for(int i=0;i<n;i++)
    {
        a[i].resize(m);
        for(int j=0;j<m;j++)
        {
            cin>>a[i][j];
        }
    }
    precalc();

    int sol=0;
    while(query>0)
    {
        query--;

        int upit;
        cin>>upit;
        upit ^= sol;
        sol = dp[(upit & MAX)];

        cout<<sol<<"\n";
    }
    return 0;
}
