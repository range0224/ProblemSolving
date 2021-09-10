#include<iostream>
#include<cstring>
using namespace std;

const int MOD = 1000000007;
int dp[5010];

int recur(int cur)
{
    int ret = 0;
    int i;
    
    if(cur == 0) return 1;
    
    if(dp[cur] != -1) return dp[cur];
    
    ret = 2 * recur(cur - 1);
    ret %= MOD;
    for(i = 1; i < cur; i++){
        ret = (ret + 1LL * recur(i - 1) * recur(cur - i - 1)) % MOD;
    }
    
    return dp[cur] = ret;
}

int main()
{
    int t;
    int n;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    memset(dp, -1, sizeof(dp));
    
    cin >> t;
    while(t--)
    {
        cin >> n;
        
        cout << recur(n) << '\n';
    }
}
