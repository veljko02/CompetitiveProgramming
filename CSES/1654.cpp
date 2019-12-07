#include<bits/stdc++.h>
#define maxn 200005
#define pb push_back
#define pii pair<int,int>
using namespace std;
 
int n;
int a[maxn];
 
int br[1<<20]; /** br[x] = number of y s.t. x | y == x, i.e. number of the subsets of x  **/
int cmp[1<<20]; /** similar but with complements, it corresponds to the second part, i.e. supersets of x, just notice that if x is a subset of y then the complement of y is subset of the complement of x **/
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    int MAXX = (1<<20) - 1;
 
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        br[a[i]]++;
        cmp[a[i] ^ MAXX]++;
    }
 
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<=MAXX;j++)
        {
            if(j & (1<<i))
            {
                br[j] += br[ j ^ (1<<i) ];
                cmp[j] += cmp[ j ^ (1<<i) ];
            }
        }
    }
 
 
    for(int i=0;i<n;i++)
    {
        cout<<br[a[i]]<<" "<<cmp[a[i] ^ MAXX]<<" "<<n - br[ a[i] ^ MAXX ]<<endl;
    }
 
    return 0;
}
