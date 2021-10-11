#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> v[1000010];

int dfs(int cur, int x, int prv)
{
    int i;
    bool leaf = true;
    int ret = 0;
    
    for(i = 0; i < v[cur].size(); i++)
    {
        if(v[cur][i] == prv) continue;
        
        ret += dfs(v[cur][i], !x, cur);
        leaf = false;
    }
    
    if(leaf && x) return 1;
    else return ret;
}

int main()
{
    int i;
    int a, b;
    int idx, idx2;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    if(n == 1)
    {
        cout << 1;
        return 0;
    }
    
    idx = -1;
    for(i = 1; i <= n; i++)
    {
        if(v[i].size() > 1)
        {
            idx = i;
            break;
        }
    }
    
    if(idx == -1) cout << max(dfs(1, 1, -1), dfs(v[1][0], 1, -1));
    else
    {
        for(i = 0; i < v[idx].size(); i++)
        {
            idx2 = -1;
            if(v[v[idx][i]].size() > 1)
            {
                idx2 = v[idx][i];
                break;
            }
        }
        
        if(idx2 == -1) cout << max(dfs(idx, 1, -1), dfs(v[idx][0], 1, -1));
        else cout << max(dfs(idx, 1, -1), dfs(idx2, 1, -1));
    }
}

