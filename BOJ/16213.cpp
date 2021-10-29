#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
vector<pair<int, pair<int, int>>> v;
vector<pair<int, int>> query;
vector<pair<int, int>> tv;
int s[200010];
int e[200010];
int ans[200010];
int par[200010];
int rnk[200010];

int find(int x)
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    if(a == b) return;
    
    if(rnk[a] < rnk[b]) par[a] = b;
    else if(rnk[a] > rnk[b]) par[b] = a;
    else
    {
        par[a] = b;
        rnk[b]++;
    }
}

int main()
{
    int q;
    int i;
    int a, b, c;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m >> q;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        
        v.push_back(make_pair(c, make_pair(a, b)));
    }
    for(i = 0; i < q; i++)
    {
        cin >> a >> b;
        
        query.push_back(make_pair(a, b));
    }
    
    sort(v.begin(), v.end());
    
    for(i = 0; i < q; i++)
    {
        s[i] = 0;
        e[i] = 1000000000;
    }
    
    while(1)
    {
        tv.clear();
        
        for(i = 0; i < q; i++)
        {
            if(s[i] > e[i]) continue;
            
            tv.push_back(make_pair((s[i] + e[i]) / 2, i));
        }
        
        if(tv.empty()) break;
        
        sort(tv.begin(), tv.end());
        
        for(i = 1; i <= n; i++)
        {
            par[i] = i;
            rnk[i] = 0;
        }
        
        idx = v.size() - 1;
        for(i = tv.size() - 1; i >= 0; i--)
        {
            while(idx >= 0 && v[idx].first >= tv[i].first)
            {
                union_(v[idx].second.first, v[idx].second.second);
                idx--;
            }
            
            if(find(query[tv[i].second].first) == find(query[tv[i].second].second))
            {
                ans[tv[i].second] = tv[i].first;
                s[tv[i].second] = tv[i].first + 1;
            }
            else e[tv[i].second] = tv[i].first - 1;
        }
    }
    
    for(i = 0; i < q; i++)
    {
        cout << ans[i] << '\n';
    }
}
