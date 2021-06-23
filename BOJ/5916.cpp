#include<iostream>
#include<vector>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
long long tree[SIZE];
long long lazy[SIZE];

void propagate(int idx, int s, int e)
{
    if(idx < len)
    {
        lazy[2*idx] += lazy[idx];
        lazy[2*idx+1] += lazy[idx];
    }
    tree[idx] += (e - s + 1) * lazy[idx];
    lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    propagate(idx,s,e);
    
    if(s > te || e < ts) return;
    else if(ts <= s && e <= te)
    {
        lazy[idx] = 1;
        propagate(idx, s, e);
        return;
    }
    
    mid = (s + e) / 2;
    
    update(2*idx,s,mid,ts,te);
    update(2*idx+1,mid+1,e,ts,te);
    
    tree[idx] = tree[2*idx] + tree[2*idx + 1];
}

long long get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    propagate(idx, s, e);
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s+e)/2;
    
    return get(2*idx, s, mid, ts, te) + get(2*idx + 1, mid + 1, e, ts, te);
}

void dfs(int cur)
{
    int i;
    
    visited[cur] = true;
    for(i=0;i<input[cur].size();i++)
    {
        if(visited[input[cur][i]]) continue;
        
        v[cur].push_back(input[cur][i]);
        dfs(input[cur][i]);
    }
}

void dfs1(int cur)
{
    int i;
    
    sz[cur] = 1;
    for(i=0;i<v[cur].size();i++)
    {
        par[v[cur][i]] = cur;
        depth[v[cur][i]] = depth[cur] + 1;
        dfs1(v[cur][i]);
        sz[cur] += sz[v[cur][i]];
        
        if(sz[v[cur][i]] > sz[v[cur][0]]) swap(v[cur][i], v[cur][0]);
    }
}

void dfs2(int cur)
{
    int i;
    
    in[cur] = cnt++;
    for(i=0;i<v[cur].size();i++)
    {
        if(i == 0) top[v[cur][i]] = top[cur];
        else top[v[cur][i]] = v[cur][i];
        
        dfs2(v[cur][i]);
    }
}

int main()
{
    int q;
    int i;
    char a;
    int b, c;
    long long ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    for(i=0;i<n-1;i++)
    {
        cin >> b >> c;
        
        input[b].push_back(c);
        input[c].push_back(b);
    }
    
    dfs(1);
    dfs1(1);
    dfs2(1);
    
    while(q--)
    {
        cin.ignore();
        
        cin >> a >> b >> c;
        
        if(a == 'P')
        {
            while(top[b] != top[c])
            {
                if(depth[top[b]] < depth[top[c]]) swap(b, c);
                
                update(1, 0, len - 1, in[top[b]], in[b]);
                b = par[top[b]];
            }
            if(depth[b] > depth[c]) swap(b, c);
            
            if(b != c) update(1, 0, len - 1, in[b] + 1, in[c]);
        }
        else
        {
            ans = 0;
            while(top[b] != top[c])
            {
                if(depth[top[b]] < depth[top[c]]) swap(b, c);
                
                ans += get(1, 0, len - 1, in[top[b]], in[b]);
                b = par[top[b]];
            }
            if(depth[b] > depth[c]) swap(b, c);
            
            if(b != c) ans += get(1, 0, len - 1, in[b] + 1, in[c]);
            
            cout << ans << '\n';
        }
    }
}
