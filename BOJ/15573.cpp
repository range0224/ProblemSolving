#include<iostream>
using namespace std;

int n, m, k;
int arr[1010][1010];
bool visited[1010][1010];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

bool in_range(int x, int y)
{
    return x >= 0 && x <= n && y >= 0 && y <= m + 1;
}

int check(int x, int y, int v)
{
    int i;
    int ret = 0;
    int nx, ny;
    
    if(x >= 1 && x <= n && y >= 1 && y <= m) ret = 1;
    
    visited[x][y] = true;
    for(i = 0; i < 4; i++)
    {
        nx = x + dx[i];
        ny = y + dy[i];
        
        if(!in_range(nx, ny) || visited[nx][ny] || arr[nx][ny] > v) continue;
        
        ret += check(nx, ny, v);
    }
    
    return ret;
}

int main()
{
    int i, j;
    int s, e;
    int mid;
    int ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m >> k;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    ans = 0;
    s = 0;
    e = 1000000;
    while(s <= e)
    {
        mid = (s + e) / 2;
        
        for(i = 0; i <= n; i++)
        {
            for(j = 0; j <= m + 1; j++)
            {
                visited[i][j] = false;
            }
        }
        
        if(check(0, 0, mid) >= k)
        {
            ans = mid;
            e = mid - 1;
        }
        else s = mid + 1;
    }
    
    cout << ans;
}
