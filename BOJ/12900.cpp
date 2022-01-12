#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
int arr[10010][2];
int dp[10010][2];

int recur(int cur, int v)
{
    if(cur > n / 2)
    {
        if(arr[cur][0] == v) return 0;
        else return 1000000;
    }
    
    if(dp[cur][v] != -1) return dp[cur][v];
    
    if(arr[cur][1] == 0)
    {
        if(arr[cur][0] == 0)
        {
            if(v == 0)
            {
                return dp[cur][v] = recur(2 * cur, 0) + recur(2 * cur + 1, 0);
            }
            else
            {
                return dp[cur][v] = min(recur(2 * cur, 1) + recur(2 * cur + 1, 1), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0)));
            }
        }
        else
        {
            if(v == 0)
            {
                return dp[cur][v] = min(recur(2 * cur, 0) + recur(2 * cur + 1, 0), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0)));
            }
            else
            {
                return dp[cur][v] = recur(2 * cur, 1) + recur(2 * cur + 1, 1);
            }
        }
    }
    else
    {
        if(arr[cur][0] == 0)
        {
            if(v == 0)
            {
                return dp[cur][v] = min(recur(2 * cur, 0) + recur(2 * cur + 1, 0), min(recur(2 * cur, 0) + recur(2 * cur + 1, 0), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0))) + 1);
            }
            else
            {
                return dp[cur][v] = min(min(recur(2 * cur, 1) + recur(2 * cur + 1, 1), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0))), recur(2 * cur, 1) + recur(2 * cur + 1, 1) + 1);
            }
        }
        else
        {
            if(v == 0)
            {
                return dp[cur][v] = min(min(recur(2 * cur, 0) + recur(2 * cur + 1, 0), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0))), recur(2 * cur, 0) + recur(2 * cur + 1, 0) + 1);
            }
            else
            {
                return dp[cur][v] = min(recur(2 * cur, 1) + recur(2 * cur + 1, 1), min(recur(2 * cur, 1) + recur(2 * cur + 1, 1), min(recur(2 * cur, 0) + recur(2 * cur + 1, 1), recur(2 * cur, 1) + recur(2 * cur + 1, 0))) + 1);
            }
        }
    }
}

int main()
{
    int t, T;
    int i;
    int ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> T;
    for(t = 1; t <= T; t++)
    {
        cin >> n >> m;
        for(i = 1; i <= n / 2; i++)
        {
            cin >> arr[i][0] >> arr[i][1];
        }
        for(i = n / 2 + 1; i <= n; i++)
        {
            cin >> arr[i][0];
        }
        
        memset(dp, -1, sizeof(dp));
        
        ans = recur(1, m);
        
        cout << "Case #" << t << ": ";
        if(ans < 1000000) cout << ans << '\n';
        else cout << "IMPOSSIBLE\n";
    }
}
