/**

  The idea was to do dp on all the subsets of the given strings. So, dp[S] where S is a subset of the given strings is the solution to 
  our problem when we consider only the strings that belong to S. When we want to compute dp[S] for some particular S we can just pass 
  through all the non-trivial subsets X of S and then combine the results for X and S/X (so we firstly have to sort the subsets 
  according to their lengths. This way we will get O(3^n) algorithm (it can be proven using the Binomial Theorem). However, that will 
  be the case only if we manage to quickly iterate over the subsets of all the sets. So, there lies the problem. However, we can fix it
  using the sparse table. We can precalculate all the sub-subsets of our subsets X when |X| is a power of 2. Then, we can easily combine
  them and efficiently iterate over the sub-subsets of any subset.

  SUBMISSIONS:
  1 - without sparse table (48/160 points TLE)
  2 - with sparse table, but with a bit slower version of it (used intervals of lenght 2^(log(n)) from the both sides) (48/160 TLE)
  3 - just checking whether the sparse table gives TLE
  4 - faster sparse table, forgot to initialize some basic dp states (e.g. the empty set) (0/160 WA)
  5 - AC
  
  This problem has taken me 2h. However, I feel like I mostly spent time doing some technical things and thinking about 
  implementation. So, I think that with some practice I can do such problems in at most 1h.
  
  In fact, I have just taken a look at the editorial. It seems that this problem can be done without sparse table (and so without some 
  strange complexity, I haven't tried to compute it yet, but I am not 100% sure that the complexity is right and that I didn't have
  luck with the tests). So, there is only a trick with helps you to quickly iterate over the subsets of an arbitrary set. So, I had
  known that I would have solved it in ~25min, maybe even less.
**/
#include<bits/stdc++.h>
#define maxn 17
#define INF 10000000
using namespace std;
 
int n;
int duz[maxn];
int sl[maxn][26];
int dp[(1<<maxn) + 5];
vector<int>sz[maxn];
vector<int>tre;
int minn[26];
string s;
vector<int>subsets[(1<<(maxn))+5];
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        duz[i]=s.size();
        for(auto x:s)
        {
            sl[i][x-'a']++;
        }
    }
 
    for(int i=1;i<(1<<n);i++)
    {
        int sub1=0;
        int sub2=0;
 
        int br=0;
        for(int j=1;j<=i;j*=2)
        {
            if(j & i)
            {
                if(br%2==0)sub1+=j;
                else sub2+=j;
                br++;
            }
        }
        sz[br].push_back(i);
 
        if(br==1)
        {
            subsets[i].push_back(0);
            subsets[i].push_back(sub1);
        }
 
        else if(br==2 || br==4 || br==8)
        {
            for(auto subsub1:subsets[sub1])
            {
                for(auto subsub2:subsets[sub2])
                {
                    subsets[i].push_back(subsub1|subsub2);
                }
            }
        }
    }
 
    subsets[0].push_back(0);
    dp[0]=0;
 
 
    for(int br=1;br<=n;br++)
    {
        for(auto subset:sz[br])
        {
            tre.clear();
            for(int j=0;j<n;j++)
            {
                if((1<<j)&subset)tre.push_back(j);
            }
 
            if(br==1)
            {
                dp[subset]=duz[tre[0]];
                continue;
            }
 
            for(int j=0;j<26;j++)minn[j]=INF;
            for(int j=0;j<br;j++)
            {
                for(int w=0;w<26;w++)
                {
                    minn[w]=min(minn[w],sl[ tre[j] ][w]);
                }
            }
            int presek=0;
            for(int j=0;j<26;j++)presek+=minn[j];
 
 
            dp[subset]=INF;
 
            int vel;
            if(br>=8)vel=8;
            else if(br>=4)vel=4;
            else if(br>=2)vel=2;
 
            int sub1=0;
            for(int w=0;w<vel;w++)
            {
                sub1+=1<<(tre[w]);
            }
 
          	int vel2=br-vel;
          	if(vel2>4)vel2=8;
          	else if(vel2>2)vel2=4;
 
          	//cout<<br<<" "<<vel<<" "<<vel2<<endl;
            int sub2=0;
            for(int w=br-1;(br-1)-w+1<=vel2;w--)
            {
                sub2+=1<<(tre[w]);
            }
 
            for(auto subsub1:subsets[sub1])
                for(auto subsub2:subsets[sub2])
                {
                    int sss1=subsub1|subsub2;
                    int sss2=subset-sss1;
 
                    if(sss1!=0 && sss2!=0)dp[subset]=min(dp[subset],dp[sss1]+dp[sss2]-presek);
                }
        }
    }
 
    cout<<dp[(1<<n)-1]+1<<endl;
    return 0;
}
