#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
long long m;
int arr[30][30];
vector<int> v;
long long dp[30];
map<long long, long long> mp[30][30];
vector<long long> tv[30][30];
vector<long long> tv2[30][30];
long long answer;

void recur(int x, int y)
{
    int i;
    long long mx;
    long long ans;
    long long sum;
    
    v.push_back(arr[x][y]);
    
    if(x + y == n + 1)
    {
        ans = v[v.size() - 1];
        sum = 0;
        for(i = v.size() - 1; i >= 0; i--)
        {
            sum += v[i];
            
            if(ans < sum) ans = sum;
        }
        
        mx = v[0];
        dp[0] = v[0];
        for(i = 1; i < v.size(); i++)
        {
            if(dp[i - 1] < 0) dp[i] = v[i];
            else dp[i] = dp[i - 1] + v[i];
            
            mx = max(mx, dp[i]);
        }
        
        if(mx > m)
        {
            v.pop_back();
            return;
        }
        else if(mx == m)
        {
            tv[x][y].push_back(ans);
        }
        else
        {
            if(mp[x][y].find(ans) == mp[x][y].end()) mp[x][y][ans] = 1;
            else mp[x][y][ans]++;
        
            tv2[x][y].push_back(ans);
        }
        
        v.pop_back();
        return;
    }
    
    if(x + 1 <= n) recur(x + 1, y);
    if(y + 1 <= n) recur(x, y + 1);
    
    v.pop_back();
}

void recur2(int x, int y)
{
    int i;
    long long mx;
    long long ans;
    long long sum;
    long long s, e, mid;
    long long idx;
    
    v.push_back(arr[x][y]);
    
    if(x + y == n + 2)
    {
        ans = v[v.size() - 1];
        sum = 0;
        for(i = v.size() - 1; i >= 0; i--)
        {
            sum += v[i];
            
            if(ans < sum) ans = sum;
        }
        
        mx = v[0];
        dp[0] = v[0];
        for(i = 1; i < v.size(); i++)
        {
            if(dp[i - 1] < 0) dp[i] = v[i];
            else dp[i] = dp[i - 1] + v[i];
            
            mx = max(mx, dp[i]);
        }
        
        if(mx > m)
        {
            v.pop_back();
            return;
        }
        else if(mx == m)
        {
            s = 0;
            e = tv2[x - 1][y].size() - 1;
            idx = -1;
            while(s <= e)
            {
                mid = (s + e) / 2;
                
                if(tv2[x - 1][y][mid] <= m - ans)
                {
                    idx = mid;
                    s = mid + 1;
                }
                else e = mid - 1;
            }
            
            answer += idx + 1;
            
            
            s = 0;
            e = tv2[x][y - 1].size() - 1;
            idx = -1;
            while(s <= e)
            {
                mid = (s + e) / 2;
                
                if(tv2[x][y - 1][mid] <= m - ans)
                {
                    idx = mid;
                    s = mid + 1;
                }
                else e = mid - 1;
            }
            
            answer += idx + 1;
        }
        else
        {
            if(mp[x - 1][y].find(m - ans) != mp[x - 1][y].end()) answer += mp[x - 1][y][m - ans];
            if(mp[x][y - 1].find(m - ans) != mp[x][y - 1].end()) answer += mp[x][y - 1][m - ans];
        }
        
        s = 0;
        e = tv[x - 1][y].size() - 1;
        idx = -1;
        while(s <= e)
        {
            mid = (s + e) / 2;
            
            if(tv[x - 1][y][mid] <= m - ans)
            {
                idx = mid;
                s = mid + 1;
            }
            else e = mid - 1;
        }
        answer += idx + 1;
        
        s = 0;
        e = tv[x][y - 1].size() - 1;
        idx = -1;
        while(s <= e)
        {
            mid = (s + e) / 2;
            
            if(tv[x][y - 1][mid] <= m - ans)
            {
                idx = mid;
                s = mid + 1;
            }
            else e = mid - 1;
        }
        answer += idx + 1;
        
        v.pop_back();
        return;
    }
    
    if(x - 1 >= 1) recur2(x - 1, y);
    if(y - 1 >= 1) recur2(x, y - 1);
    
    v.pop_back();
}

int main()
{
    int i, j;
    
    cin >> n >> m;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    if(n == 1)
    {
        if(arr[1][1] == m) cout << 1;
        else cout << 0;
        
        return 0;
    }
    
    recur(1, 1);

    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            sort(tv[i][j].begin(), tv[i][j].end());
            sort(tv2[i][j].begin(), tv2[i][j].end());
        }
    }

    recur2(n, n);
    
    cout << answer;
}
