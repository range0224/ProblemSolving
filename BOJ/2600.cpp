#include<iostream>
#include<string>
#include<cstring>
using namespace std;

int arr[3];
int dp[510][510];
string ans = "BA";

int recur(int a, int b)
{
    int i;
    
    if(a < arr[0] && b < arr[0]) return 0;
    
    if(dp[a][b] != -1) return dp[a][b];
    
    for(i = 0; i < 3; i++)
    {
        if(a >= arr[i] && recur(a - arr[i], b) == 0) return dp[a][b] = 1;
        if(b >= arr[i] && recur(a, b - arr[i]) == 0) return dp[a][b] = 1;
    }
    
    return dp[a][b] = 0;
}

int main()
{
    int i;
    int a, b;
    
    memset(dp, -1, sizeof(dp));
    
    cin >> arr[0] >> arr[1] >> arr[2];
    for(i = 0; i < 5; i++)
    {
        cin >> a >> b;
        
        cout << ans[recur(a, b)] << '\n';
    }
}
