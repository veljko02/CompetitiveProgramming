/*
  https://csacademy.com/contest/ioi-2016-training-round-5/task/balanced-string/solution/
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

string s,s2;
vector<int>v;
int minn[2],maxx[2];
bool ok()
{
    int sz = s.size();
    int poc = 0;
    for(int i=0;i<sz;i++)
    {
        int nxt = (i + 1) % sz;
        if(s[i] != s[nxt])
        {
            poc = nxt;
        }
    }

    s2.clear();
    for(int i=0;i<sz;i++)
    {
        s2.push_back(s[poc]);
        poc++;
        poc %= sz;
    }
    for(int i=0;i<sz;i++)
    {
        s[i] = s2[i];
    }

    v.clear();
    int tre = 0;
    int start = 0;
    int zasad = 0;
    while(tre < sz)
    {
        if(s[tre] == s[start])
        {
            zasad++;
        }
        else
        {
            v.pb(zasad);
            start = tre;
            zasad = 1;
        }
        if(tre == sz - 1)
        {
            v.pb(zasad);
        }
        tre++;
    }

    minn[0] = minn[1] = sz + 100;
    maxx[0] = maxx[1] = -1;
    int v_sz = v.size();
    for(int i=0;i<v_sz;i++)
    {
        int tre = i % 2;
        minn[tre] = min(minn[tre],v[i]);
        maxx[tre] = max(maxx[tre],v[i]);
    }

    s.clear();
    if(maxx[0] == -1 || maxx[1] == -1)return true;
    if(maxx[0] == 1 && maxx[1] == 1)return true;
    if(maxx[0] != 1 && maxx[1] != 1)return false;
    if(maxx[0] != 1)
    {
        if(maxx[0] - minn[0] >= 2)return false;
        for(int i=0;i<v_sz;i+=2)
        {
            if(v[i] == maxx[0])s.pb('A');
            else s.pb('B');
        }
    }
    else
    {
        if(maxx[1] - minn[1] >= 2)return false;
        for(int i=1;i<v_sz;i+=2)
        {
            if(v[i] == maxx[1])s.pb('A');
            else s.pb('B');
        }
    }
    return ok();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin>>t;
    while(t>0)
    {
        t--;
        cin>>s;
        cout<<ok()<<"\n";
    }
    return 0;
}
