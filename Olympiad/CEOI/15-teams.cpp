/**
    I guess that the following explanation will be a bit confusing. Sorry for that!
    
    So, the idea was to use dp.
    Let A be an array of length n which contains k teams, then we define dp[x][k] to be the number of distinct array that begins with A 
    and that has length equal to n+x. One can notice that A is irrelevant, I have just formulated dp state that way because I haven't 
    come up with any better explanation. Anyway, now the idea is to go through the given array and fix the point where some 
    lexicographically smaller array B (that is also a partition of the people into teams) differs from the given array. Then we can
    easily get how many such arrays exist using our dp. Also, dp has too many states so we have to compute it gradually during the 
    fixing phases. 
    
    SUBMISSIONS
    1 - I made a stupid mistake so it worked only when the array in the input is 1 2 3 4 ... n and when n<=1000 (10/100 WA)
    2 - I fixed the mistake (just changed a letter) and then it worked when n<=1000 (70/100 WA)
    3 - I did dp gradually but I forgot to alter maxn, so it still worked just for n<=1000 (70/100 WA)
    4 - I altered maxn (AC)
    
    This problem was easy. I basically solved it in ~10min. However, I firstly overlooked that I couldn't just compute the 
    number of different partition using dp and then using it get the result. So, I typed that even though it was obvious that it would
    not work. So, I spent ~30min coding and thinking about that idea. Then, I realized that it was wrong and then easily altered it and
    got AC after additional ~40min. So, I think that with some practice I can do such problems in ~30min. It seems that I should stop 
    completely following my intuition and think a bit more before starting to code something.
**/
#include<bits/stdc++.h>
#define maxn 10005
#define mod 1000007
#define ll long long
using namespace std;
 
int n;
int a[maxn];
ll dp[2][maxn];
int g[maxn];
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    g[1]=1;
    for(int i=2;i<=n;i++)g[i]=max(g[i-1],a[i]);
 
    int prev=0;
    int curr=1;
 
    long long ans=0;
    for(int i=n;i>=2;i--)
    {
        if(i!=n)
        {
            int d=n-i;
            for(int k=1;k+d<=n;k++)
            {
                if(d==1)dp[curr][k]=k+1;
                else
                {
                    dp[curr][k]=dp[prev][k+1]+k*dp[prev][k];
                    dp[curr][k]%=mod;
                }
            }
        }
 
 
        ll br;
        if(i==n)
        {
            br=1;
        }
        else if(g[i]==g[i-1])
        {
            br=dp[curr][g[i]];
        }
        else
        {
            br=dp[curr][g[i]-1];
        }
 
 
 
 
        ans+=(a[i]-1)*br;
        ans%=mod;
 
        swap(curr,prev);
    }
 
    cout<<(ans+1)%mod<<endl;
    return 0;
}
