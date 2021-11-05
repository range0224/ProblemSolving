#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
vector<int> v[15];
int prefix[15][2010];
int dp[15][2010];

bool comp(int a, int b)
{
    return a > b;
}

int main()
{
    int i, j, k;
    int a, b;
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> a >> b;
        
        v[b].push_back(a);
    }
    
    for(i = 1; i <= 10; i++)
    {
        sort(v[i].begin(), v[i].end(), comp);
    }
    
    for(i = 1; i <= 10; i++)
    {
        if(v[i].empty()) continue;
        
        prefix[i][0] = v[i][0];
        for(j = 1; j < v[i].size(); j++)
        {
            prefix[i][j] = prefix[i][j - 1] + v[i][j] + 2 * j;
        }
    }
    
    for(i = 1; i <= 10; i++)
    {
        for(j = 0; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j];
            for(k = 1; k <= j && k <= v[i].size(); k++)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + prefix[i][k - 1]);
            }
        }
    }
    
    cout << dp[10][m];
}
