#include<iostream>
#include<algorithm>
using namespace std;

int arr[5][5];
int dir[20];
int pos[20][2];
bool die[20];
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int ans;

bool in_range(int x, int y)
{
    return x >= 0 && x < 4 && y >= 0 && y < 4;
}

void move(int sx, int sy)
{
    int i, j;
    int x, y;
    int nx, ny, ndir;
    
    for(i = 1; i <= 16; i++)
    {
        if(die[i]) continue;
        
        x = pos[i][0];
        y = pos[i][1];
        
        for(j = 0; j < 8; j++)
        {
            ndir = (dir[i] + j) % 8;
            nx = x + dx[ndir];
            ny = y + dy[ndir];
            
            if(in_range(nx, ny) && (nx != sx || ny != sy)) break;
        }
        
        if(j == 8) continue;
        
        if(arr[nx][ny] != 0)
        {
            arr[x][y] = arr[nx][ny];
            pos[arr[x][y]][0] = x;
            pos[arr[x][y]][1] = y;
        }
        else arr[x][y] = 0;
        
        arr[nx][ny] = i;
        pos[i][0] = nx;
        pos[i][1] = ny;
        dir[i] = ndir;
    }
}

void recur(int x, int y, int sdir, int sum)
{
    int i, j;
    int nx, ny, ndir;
    int fish;
    int arr2[5][5];
    int dir2[20];
    
    fish = arr[x][y];
    
    ans = max(ans, sum + fish);
    
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            arr2[i][j] = arr[i][j];
        }
    }
    for(i = 1; i <= 16; i++)
    {
        dir2[i] = dir[i];
    }
    
    die[fish] = true;
    arr[x][y] = 0;
    
    move(x, y);
    
    for(i = 1; i <= 3; i++)
    {
        nx = x + i * dx[sdir];
        ny = y + i * dy[sdir];
        
        if(!in_range(nx, ny)) break;
        
        if(arr[nx][ny])
        {
            ndir = dir[arr[nx][ny]];
            recur(nx, ny, ndir, sum + fish);
        }
    }
    die[fish] = false;
    arr[x][y] = fish;
    pos[fish][0] = x;
    pos[fish][1] = y;
    
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            arr[i][j] = arr2[i][j];
            
            pos[arr[i][j]][0] = i;
            pos[arr[i][j]][1] = j;
        }
    }
    for(i = 1; i <= 16; i++) dir[i] = dir2[i];
}

int main()
{
    int i, j;
    int a, b;
    
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
            cin >> a >> b;
            
            arr[i][j] = a;
            pos[a][0] = i;
            pos[a][1] = j;
            dir[a] = b - 1;
        }
    }
    
    recur(0, 0, dir[arr[0][0]], 0);
    
    cout << ans;
}
