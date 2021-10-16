#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int n;
int arr[25][25];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int ans;

bool in_range(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

void move(int dir)
{
    int i;
    int x, y;
    int nx, ny;
    queue<int> que;
    
    for(i = 0; i < n; i++)
    {
        if(dir == 0)
        {
            x = n - 1;
            y = i;
        }
        else if(dir == 1)
        {
            x = i;
            y = n - 1;
        }
        else if(dir == 2)
        {
            x = 0;
            y = i;
        }
        else
        {
            x = i;
            y = 0;
        }
        
        nx = x;
        ny = y;
        while(in_range(nx, ny))
        {
            if(arr[nx][ny]) que.push(arr[nx][ny]);
            
            arr[nx][ny] = 0;
            nx += dx[dir];
            ny += dy[dir];
        }
        
        nx = x;
        ny = y;
        while(!que.empty())
        {
            arr[nx][ny] = que.front();
            que.pop();
            if(!que.empty() && que.front() == arr[nx][ny])
            {
                arr[nx][ny] *= 2;
                que.pop();
            }
            nx += dx[dir];
            ny += dy[dir];
        }
    }
}

void recur(int depth)
{
    int arr2[25][25];
    int i, j, dir;
    
    if(depth == 5)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                ans = max(ans, arr[i][j]);
            }
        }
        return;
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            arr2[i][j] = arr[i][j];
        }
    }
    
    for(dir = 0; dir < 4; dir++)
    {
        move(dir);
        recur(depth + 1);
        
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                arr[i][j] = arr2[i][j];
            }
        }
    }
    
    //jubgubhigvtc tfvbgy
    //_POSIX_CLOCKRES_MIN
}

int main()
{
    int ioimninmoko, j;
    
    cin >> n;
    for(ioimninmoko = 0; ioimninmoko < n; ioimninmoko++)
    {
        for(j = 0; j < n; j++)
        {
            cin >> arr[ioimninmoko][j];
        }
    }
    
    recur(0);
    
    cout << ans;
}
