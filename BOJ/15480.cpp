#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int> input[100010];
vector<int> v[100010];
int par[20][100010];
int depth[100010];
bool visited[100010];

void dfs(int cur)
{
    int i;
    
    visited[cur] = true;
    for(i = 0; i < input[cur].size(); i++){
        if(visited[input[cur][i]]) continue;
        
        v[cur].push_back(input[cur][i]);
        par[0][input[cur][i]] = cur;
        depth[input[cur][i]] = depth[cur] + 1;
        dfs(input[cur][i]);
    }
}

int get_lca(int a, int b)
{
    int i;
    int gap;
    
    if(depth[a] < depth[b]) swap(a, b);
    
    gap = depth[a] - depth[b];
    for(i = 19; i >= 0; i--)
    {
        if(gap & (1 << i)) a = par[i][a];
    }
    
    for(i = 19; i >= 0; i--)
    {
        if(par[i][a] != par[i][b])
        {
            a = par[i][a];
            b = par[i][b];
        }
    }
    
    if(a == b) return a;
    else return par[0][a];
}

int main()
{
    int q;
    int i, j;
    int a, b, c;
    int x, y, z;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        
        input[a].push_back(b);
        input[b].push_back(a);
    }
    
    dfs(1);
    
    for(i = 1; i < 20; i++)
    {
        for(j = 1; j <= n; j++){
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
    
    cin >> q;
    while(q--)
    {
        cin >> a >> b >> c;
        
        if(a == 1)
        {
            cout << get_lca(b, c) << '\n';
            continue;
        }
        
        if(get_lca(a, b) == 1 && get_lca(a, c) == 1) cout << get_lca(b, c) << '\n';
        else if(get_lca(a, b) == 1) cout << get_lca(a, c) << '\n';
        else if(get_lca(a, c) == 1) cout << get_lca(a, b) << '\n';
        else
        {
            x = get_lca(a, b);
            y = get_lca(a, c);
            z = get_lca(b, c);
            
            if(depth[x] >= depth[y] && depth[x] >= depth[z]) cout << x << '\n';
            else if(depth[y] >= depth[x] && depth[y] >= depth[z]) cout << y << '\n';
            else cout << z << '\n';
        }
    }
}
