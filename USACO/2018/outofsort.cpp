/**
  I have no idea why this thing works, maybe after some computations it ends up being the same as the official solution. Anyway, I made
  a bug when I tried to code some solution that did not work (I typed i instead of a[i] at some place), so I ended up with this and got
  AC even though I did not deserve it XD
**/

#include<bits/stdc++.h>
#define maxn 100005
#define ll long long
#define pii pair<int,int>
#define pb push_back
using namespace std;


int n;
int a[maxn];
int poz[maxn];

bool cmp(int levo,int desno)
{
    if(a[levo] != a[desno])return a[levo] < a[desno];
    return levo < desno;
}

int l[maxn];
int r[maxn];
int tree[4*maxn + 5];

void update(int v,int l,int r,int ind)
{
    if(l>r || ind>r || l>ind)return;
    if(l==r)
    {
        tree[v] = 1;
        return;
    }
    int mid = (l+r)/2;
    update(2*v,l,mid,ind);
    update(2*v+1,mid+1,r,ind);
    tree[v] = tree[2*v] + tree[2*v+1];
}
int izbroj(int v,int l,int r,int lt,int rt)
{
    if(l>r || l>rt || lt>r || lt>rt)return 0;
    if(lt<=l && r<=rt)return tree[v];
    int mid = (l+r)/2;
    return izbroj(2*v,l,mid,lt,rt) + izbroj(2*v+1,mid+1,r,lt,rt);
}

int main()
{
    ifstream cin("sort.in");
    ofstream cout("sort.out");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        poz[i] = i;
    }
    sort(poz,poz+n,cmp);
    for(int i=0;i<n;i++)
    {
        a[poz[i]] = i;
    }

    for(int i=0;i<n;i++)
    {
        l[i] = izbroj(1,0,n-1,i+1,n-1);
        update(1,0,n-1,a[i]);
    }
    for(int i=0;i<=4*maxn;i++)
    {
        tree[i] = 0;
    }
    for(int i=n-1;i>=0;i--)
    {
        r[i] = izbroj(1,0,n-1,0,i-1);
        update(1,0,n-1,a[i]);
    }

    int sol = 0;
    for(int i=0;i<n;i++)
    {
        sol = max(sol, min(l[i],r[i]));
    }
    cout<<sol + 1<<endl;
    return 0;
}

