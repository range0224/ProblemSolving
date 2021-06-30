#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 20;
const int len = 1 << 19;
int n;
vector<pair<int,int>> v;
vector<int> tv;
map<int, int> m;
int tree[SIZE];
int lazy[SIZE];

void propagate(int idx, int s, int e)
{
    if(idx < len)
    {
        lazy[2*idx] = max(lazy[2*idx], lazy[idx]);
        lazy[2*idx+1] = max(lazy[2*idx+1], lazy[idx]);
    }
    tree[idx] = max(tree[idx], lazy[idx]);
    lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
    int mid;
    
    propagate(idx, s, e);
    
    if(s > te || e < ts) return;
    else if(ts <= s && e <= te)
    {
        lazy[idx] = value;
        propagate(idx, s, e);
        return;
    }
    
    mid = (s + e) / 2;
    
    update(2*idx, s, mid, ts, te, value);
    update(2*idx+1, mid+1, e, ts, te, value);
    
    tree[idx] = max(tree[2*idx], tree[2*idx+1]);
}

int get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    propagate(idx, s, e);
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
    int i;
    int idx;
    int a, b;
    int ans = 0;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i=0;i<n;i++)
    {
        cin >> a >> b;
        
        v.push_back(make_pair(b, a + b - 1));
        tv.push_back(b);
        tv.push_back(a + b - 1);
    }
    
    sort(tv.begin(),tv.end());
    
    m[tv[0]] = 1;
    idx = 2;
    for(i=1;i<tv.size();i++)
    {
        if(tv[i] == tv[i-1]) continue;
        
        m[tv[i]] = idx++;
    }
    
    for(i=0;i<v.size();i++)
    {
        v[i].first = m[v[i].first];
        v[i].second = m[v[i].second];
    }
    
    for(i=0;i<v.size();i++)
    {
        update(1, 0, len - 1, v[i].first, v[i].second, get(1, 0, len - 1, v[i].first, v[i].second) + 1);
        
        ans = max(ans, get(1, 0, len - 1, v[i].first, v[i].second));
    }
    
    cout << ans;
}
