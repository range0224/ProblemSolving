#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, s;
vector<int> v[100010];
int visited[100010];
int cnt = 1;

void dfs(int cur)
{
    int i;
    
    visited[cur] = cnt++;
    for(i = 0; i < v[cur].size(); i++)
    {
        if(!visited[v[cur][i]]) dfs(v[cur][i]);
    }
}

int main()
{
    int i;
    int a, b;
    
    cin >> n >> m >> s;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    for(i = 1; i <= n; i++) sort(v[i].begin(), v[i].end());
    
    dfs(s);
    
    for(i = 1; i <= n; i++)
    {
        cout << visited[i] << '\n';
    }
}
