#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
long long a[500010];
long long b[500010];
long long arr[1000010];
int cnt[1000010];
long long prefix1[1000010];
long long prefix2[1000010];
long long dp[1000010];
int prv[2000010];

int main()
{
    int i;
    int s1, s2;
    int idx;
    int x;
    long long mn;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for(i = 0; i < m; i++)
    {
        cin >> b[i];
    }
    
    s1 = 0;
    s2 = 0;
    idx = 1;
    cnt[0] = 1000000;
    while(s1 < n && s2 < m)
    {
        prefix1[idx] = prefix1[idx - 1];
        prefix2[idx] = prefix2[idx - 1];
        cnt[idx] = cnt[idx - 1];
        
        if(a[s1] < b[s2])
        {
            cnt[idx]++;
            prefix1[idx] += a[s1];
            arr[idx++] = a[s1++];
        }
        else
        {
            cnt[idx]--;
            prefix2[idx] += b[s2];
            arr[idx++] = b[s2++];
        }
    }
    while(s1 < n)
    {
        cnt[idx] = cnt[idx - 1] + 1;
        prefix1[idx] = prefix1[idx - 1] + a[s1];
        prefix2[idx] = prefix2[idx - 1];
        arr[idx++] = a[s1++];
    }
    while(s2 < m)
    {
        cnt[idx] = cnt[idx - 1] - 1;
        prefix1[idx] = prefix1[idx - 1];
        prefix2[idx] = prefix2[idx - 1] + b[s2];
        arr[idx++] = b[s2++];
    }
    
    s1 = 0;
    s2 = 0;
    for(i = 1; i < idx; i++)
    {
        dp[i] = 1LL << 60;
        
        if(cnt[i] == cnt[i - 1] + 1) s1++;
        else s2++;
        
        x = prv[cnt[i]];
        
        if(x)
        {
            dp[i] = dp[x] + abs((prefix1[i] - prefix1[x]) - (prefix2[i] - prefix2[x]));
        }
        else if(cnt[i] == 1000000)
        {
            dp[i] = abs(prefix1[i] - prefix2[i]);
        }
        
        mn = 1LL << 60;
        if(cnt[i] == cnt[i - 1] + 1)
        {
            if(s2 != 0) mn = min(mn, abs(arr[i] - b[s2 - 1]));
            if(s2 != m) mn = min(mn, abs(arr[i] - b[s2]));
        }
        else
        {
            if(s1 != 0) mn = min(mn, abs(arr[i] - a[s1 - 1]));
            if(s1 != n) mn = min(mn, abs(arr[i] - a[s1]));
        }
        
        dp[i] = min(dp[i], dp[i - 1] + mn);
        
        prv[cnt[i]] = i;
    }
    
    cout << dp[idx - 1];
}
