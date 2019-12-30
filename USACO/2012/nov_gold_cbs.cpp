/**
  So, we look on ( as on 1 and on ) as on -1. Then, we basically have an array of n<=50000 vectors of the same size k<=10 and we want to 
  count the number of subarrays of its consecutive elements s.t. 
      1) its borders are equal
      2) there are no elements in between its borders which are bigger than its borders (in at least one coordinate) 
  For each vector we can easily find the rigthmost vector smaller than the one we are currently considering and which is to the left of 
  our current vector. We can do that using stack.
  Now, we have to deal with the first condition. So, we can just iterate through the array from left to right and keep a deque for each
  vector (map<vector,deque>). Then, if we are currently dealing with some vector, we can firstly get rid of the indices which are too 
  left (smaller than the already computed rightmost index for our current vector) and then all the other indices in the deque will work
  with our current index, so we can add the deque size to the solution. And now it only remains to add our current index to the deque.
  So, the key is that the rightmost array is increasing when we consider only the indices which save the same vector.
**/

#include<bits/stdc++.h>
#define pii pair<int,int>
#define ll long long
#define pll pair<ll,ll>
#define pb push_back
#define INF 1000000000000000000 /** PROVERI INF **/
#define maxn 50005 /** PROVERI MAXN **/
#define mod 998244353 /** PROVERI MOD**/
#define x first
#define y second
#define vek second
using namespace std;

map<char,int>mp;

int n,k;
string niz;
int s[maxn][11];
map<vector<int>,deque<int>>mq;

deque<int>small;

int left_small[maxn];
vector<int>v;
int main()
{
    mp['('] = 1;
    mp[')'] = -1;
    ifstream cin("cbs.in");
    ofstream cout("cbs.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>k>>n;
    for(int i=0;i<k;i++)
    {
        cin>>niz;
        s[0][i] = 0;
        for(int j=1;j<=n;j++)
        {
            left_small[j] = -1;
            s[j][i] = s[j-1][i] + mp[niz[j - 1]];
        }
    }

    for(int i=0;i<k;i++)
    {
        while(!small.empty())small.pop_back();
        for(int j=0;j<=n;j++)
        {
            while(!small.empty() && s[small.front()][i] >= s[j][i])
            {
                small.pop_front();
            }
            if(!small.empty())
            {
                left_small[j] = max(left_small[j], small.front());
            }
            small.push_front(j);
        }
    }

    ll sol = 0;
    for(int i=0;i<=n;i++)
    {
        v.clear();
        for(int j=0;j<k;j++)v.pb(s[i][j]);

        while(!mq[v].empty() && mq[v].back() < left_small[i])
        {
            mq[v].pop_back();
        }

        sol += mq[v].size();
        mq[v].push_front(i);
    }

    cout<<sol<<endl;
    return 0;
}
