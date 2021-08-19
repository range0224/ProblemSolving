#include<iostream>
#include<vector>
using namespace std;

int n, m;
vector<int> v[200010];
int depth[200010], in[200010], out[200010];
bool visited[200010];
int tree[200010];
int cnt = 1;

void update(int idx)
{
    while(idx <= n)
    {
        tree[idx]++;
        idx += (idx & (-idx));
    }
}

int get(int idx)
{
    int ret = 0;
    
    while(idx >= 1)
    {
        ret += tree[idx];
        idx -= (idx & (-idx));
    }
    
    return ret;
}

void dfs(int cur)
{
    int i;
    
    visited[cur] = true;
    
    in[cur] = cnt++;
    for(i = 0; i < v[cur].size(); i++)
    {
        if(visited[v[cur][i]]) continue;
        
        depth[v[cur][i]] = depth[cur] + 1;
        dfs(v[cur][i]);
    }
    out[cur] = cnt - 1;
}

int main()
{
    int q;
    int i;
    int a, b;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    dfs(m);
    
    cin >> q;
    while(q--)
    {
        cin >> a >> b;
        
        if(a == 1)
        {
            update(in[b]);
        }
        else
        {
            cout << 1LL * (depth[b] + 1) * (get(out[b]) - get(in[b] - 1)) << '\n';
        }
    }
}
