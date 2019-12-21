/*
So, the idea is to compute the maximum cardinality of a valid set that contains a trapezoid for each given trapezoid. We also compute
the number of way to achieve that cardinality. We do that using dp, sweep line and some data structure.
So, we create points (a,c) and (b,d) out of each trapezoid and sort them according to their x-coordinate in increasing order. Also, we 
should remember whether the point represent the left side of a rectangle (a,c) or the right (b,d). Now, we iterate over those sorted 
points and do the following:

1) Our current point is of the "left" type
  We compute the two mentioned values for that trapezoid.
2) Our current point is of the "right" type
  We just update our data structure with the already computed two values for that interval. 
*/

#include <bits/stdc++.h>
#define maxn 100005
#define pii pair<int,int>
#define x first
#define y second
#define ll long long
#define mod 30013
#define MAX 200000
using namespace std;
 
struct djoka
{
    int x,y,type;
};
 
int n;
djoka niz[2*maxn];
int maxx[maxn];
ll num[maxn];
 
int maks[4*MAX + 5];
ll br[4*MAX + 5];
void update(int v,int l,int r,int lt,int rt,int bigg,int broj)
{
    if(l>r || l>rt || lt>r || lt>rt)return;
    if(lt<=l && r<=rt)
    {
        if(maks[v] == bigg)
        {
            br[v] += broj;
            br[v] %= mod;
        }
        else if(maks[v] < bigg)
        {
            br[v] = broj;
            maks[v] = bigg;
        }
        return;
    }
    int mid = (l+r)/2;
    update(2*v,l,mid,lt,rt,bigg,broj);
    update(2*v+1,mid+1,r,lt,rt,bigg,broj);
}
int najv(int v,int l,int r,int ind)
{
    if(l>r || l>ind || r<ind)return 0;
    if(l==r)return maks[v];
    int mid = (l+r)/2;
    if(ind<=mid)return max(maks[v],najv(2*v,l,mid,ind));
    return max(maks[v],najv(2*v+1,mid+1,r,ind));
}
ll broj(int v,int l,int r,int ind,int maksimus)
{
    if(l>r || l>ind || ind>r)return 0;
    if(l==r)
    {
        if(maks[v] == maksimus)return br[v];
        return 0;
    }
    int mid = (l+r)/2;
    ll uk = 0;
    if(maks[v] == maksimus)uk += br[v];
    if(ind<=mid)return (uk + broj(2*v,l,mid,ind,maksimus))%mod;
    return (uk + broj(2*v+1,mid+1,r,ind,maksimus))%mod;
}
 
bool cmp_x(djoka levi,djoka desni)
{
    if(levi.x!=desni.x)return levi.x < desni.x;
    return levi.type < desni.type;
}
bool cmp_y(djoka levi,djoka desni)
{
    if(levi.y!=desni.y)return levi.y < desni.y;
    return levi.type < desni.type;
}
 
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>niz[2*i].x>>niz[2*i+1].x>>niz[2*i].y>>niz[2*i+1].y;
        niz[2*i].type = i+1;
        niz[2*i+1].type = -(i+1);
    }
    sort(niz,niz + 2*n,cmp_y);
    for(int i=0;i<2*n;i++)
    {
        niz[i].y = i;
    }
    sort(niz,niz + 2*n,cmp_x);
    for(int i=0;i<2*n;i++)
    {
        niz[i].x = i;
    }
    update(1,0,MAX,0,MAX,0,1);
    for(int i=0;i<2*n;i++)
    {
        int ind = abs(niz[i].type) - 1;
        if(niz[i].type > 0)
        {
            maxx[ind] = najv(1,0,MAX,niz[i].y) + 1;
            num[ind] = broj(1,0,MAX,niz[i].y,maxx[ind] - 1);
        }
        else
        {
            update(1,0,MAX,niz[i].y+1,MAX,maxx[ind],num[ind]);
        }
    }
 
    int sol_max = 0;
    ll sol_br = 0;
    for(int i=0;i<n;i++)
    {
        if(sol_max == maxx[i])
        {
            sol_br += num[i];
            sol_br %= mod;
        }
        else if(sol_max < maxx[i])
        {
            sol_br = num[i];
            sol_max = maxx[i];
        }
    }
 
    cout<<sol_max<<" "<<sol_br<<endl;
    return 0;
}
