#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int n, m, x;
vector<int> v[100010];
vector<int> rv[100010];
bool visited[100010];

int dfs(int cur, vector<int> v[100010])
{
    int i;
    int ret = 1;
    
    visited[cur] = true;
    for(i = 0; i < v[cur].size(); i++)
    {
        if(!visited[v[cur][i]]) ret += dfs(v[cur][i], v);
    }
    
    return ret;
}

int main()
{
    int i;
    int a, b;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m >> x;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        rv[b].push_back(a);
    }
    
    a = dfs(x, v);
    memset(visited, false, sizeof(visited));
    b = dfs(x, rv);
    
    cout << b << ' ' << n - a + 1;
}
