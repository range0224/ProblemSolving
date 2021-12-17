#include<iostream>
#include<vector>
using namespace std;

int n;
int need[5];
int arr[20][5];
bool visited[20];
int mn;
int sum[5];
vector<int> ans;

void recur(int cur)
{
    int i;
    vector<int> v;
    
    if(cur == n)
    {
        for(i = 0; i < 4; i++) if(sum[i] < need[i]) return;
        
        if(mn > sum[4])
        {
            mn = sum[4];
            
            for(i = 0; i < n; i++)
            {
                if(visited[i]) v.push_back(i);
            }
            
            ans = v;
        }
        if(mn == sum[4])
        {
            for(i = 0; i < n; i++)
            {
                if(visited[i]) v.push_back(i);
            }
            
            if(ans.empty()) ans = v;
            
            for(i = 0; i < ans.size() && i < v.size(); i++)
            {
                if(ans[i] < v[i]) return;
                else if(ans[i] > v[i])
                {
                    ans = v;
                    return;
                }
            }
            if(i == v.size()) ans = v;
        }
        return;
    }
    
    for(i = 0; i < 5; i++)
    {
        sum[i] += arr[cur][i];
    }
    visited[cur] = true;
    recur(cur + 1);
    
    for(i = 0; i < 5; i++)
    {
        sum[i] -= arr[cur][i];
    }
    visited[cur] = false;
    recur(cur + 1);
}

int main()
{
    int i, j;
    
    cin >> n;
    for(i = 0; i < 4; i++) cin >> need[i];
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < 5; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    mn = 1000000000;
    recur(0);
    
    if(mn == 1000000000) cout << -1;
    else cout << mn << '\n';
    
    for(i = 0; i < ans.size(); i++) cout << ans[i] + 1 << ' ';
}

