#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int a, b;
char arr[110][110];
char shape[5][5] = {"###", "#..", "###"};

bool in_range(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

int check(int x, int y, int size)
{
    int i, j, k, l;
    int ret = 0;
    bool check[110][110] = {false};
    
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            for(k = x + i * size; k < x + (i + 1) * size; k++)
            {
                for(l = y + j * size; l < y + (j + 1) * size; l++)
                {
                    if(!in_range(k, l)) return 1000000000;
                    
                    check[k][l] = true;
                    
                    if(arr[k][l] == '.' && shape[i][j] == '#') ret += a;
                    else if(arr[k][l] == '#' && shape[i][j] == '.') ret += b;
                }
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(!check[i][j] && arr[i][j] == '#') ret += b;
        }
    }
    
    return ret;
}

int main()
{
    int i, j, k;
    int ans;
    
    cin >> n >> m;
    cin >> a >> b;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            cin >> arr[i][j];
        }
    }
    
    ans = 1000000000;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            for(k = 1; k < 30; k++)
            {
                ans = min(ans, check(i, j, k));
            }
        }
    }
    
    cout << ans;
}
