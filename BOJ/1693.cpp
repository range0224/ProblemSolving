#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
vector<int> v[100010];
int dp[100010][400];
bool visited[100010];
pair<int, int> mn[100010][2];

int dfs(int cur, int p, int color)
{
    int i, j;
    vector<pair<int, int>> tv;
    int sum;
    int ret = 1 << 30;
    
    if(dp[cur][color] != -1) return dp[cur][color];
    
    if(!visited[cur])
    {
        for(i=0;i<v[cur].size();i++)
        {
            if(v[cur][i] == p) continue;
            
            tv.clear();
            for(j=1;j<400;j++)
            {
                tv.push_back(make_pair(dfs(v[cur][i], cur, j), j));
            }
            
            sort(tv.begin(), tv.end());
            
            mn[v[cur][i]][0] = tv[0];
            mn[v[cur][i]][1] = tv[1];
        }
    }
    
    visited[cur] = true;
    
    sum = color;
    for(i=0;i<v[cur].size();i++)
    {
        if(mn[v[cur][i]][0].second == color) sum += mn[v[cur][i]][1].first;
        else sum += mn[v[cur][i]][0].first;
    }
        
    ret = min(ret, sum);
    
    return dp[cur][color] = ret;
}

int main()
{
    int i;
    int a, b;
    int ans;
    
    cin >> n;
    for(i=0;i<n-1;i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    memset(dp, -1, sizeof(dp));
    
    ans = 1<<30;
    for(i=1;i<400;i++)
    {
        ans = min(ans, dfs(1, 0, i));
    }
    
    cout << ans;
}
