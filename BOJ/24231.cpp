#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int MOD = 1000000007;
string str;
long long dp[310][310];

long long recur(int s, int e)
{
    int i;
    long long ret = 0;
    long long a, b;
    
    if(s > e) return 1;
    
    if(dp[s][e] != -1) return dp[s][e];
    
    for(i = s + 1; i <= e; i++)
    {
        if(str[i] != str[s])
        {
            a = recur(s + 1, i - 1);
            b = recur(i + 1, e);
            
            if(a && b) ret = (ret + a * b) % MOD;
        }
    }
    
    return dp[s][e] = ret;
}

int main()
{
    cin >> str;
    
    memset(dp, -1, sizeof(dp));
    
    cout << recur(0, str.length() - 1);
}
