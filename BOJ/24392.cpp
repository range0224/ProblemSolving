#include<iostream>
using namespace std;

const int MOD = 1000000007;
int n, m;
int arr[1010][1010];
long long dp[1010][1010];

int main()
{
    int i, j, k;
    long long sum;
    
    cin >> n >> m;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    for(j = 1; j <= m; j++) dp[n][j] = arr[n][j];
    
    for(i = n - 1; i >= 1; i--)
    {
        for(j = 1; j <= m; j++)
        {
            if(!arr[i][j]) continue;
            
            for(k = -1; k <= 1; k++)
            {
                dp[i][j] += dp[i + 1][j + k];
                dp[i][j] %= MOD;
            }
        }
    }
    
    sum = 0;
    for(j = 1; j <= m; j++)
    {
        sum += dp[1][j];
    }
    
    cout << sum % MOD;
}
