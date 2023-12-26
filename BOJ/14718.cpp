#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
int arr[110][3];
vector<int> v[3];

bool check(int a, int b, int c)
{
    int i;
    int cnt = 0;
    
    for(i = 0; i < n; i++)
    {
        if(a >= arr[i][0] && b >= arr[i][1] && c >= arr[i][2]) cnt++;
    }
    
    return cnt >= m;
}

int main()
{
    int i, j, k;
    int ans;
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < 3; j++)
        {
            cin >> arr[i][j];
            
            v[j].push_back(arr[i][j]);
        }
    }
    
    ans = 1 << 30;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            for(k = 0; k < n; k++)
            {
                if(check(v[0][i], v[1][j], v[2][k])) ans = min(ans, v[0][i] + v[1][j] + v[2][k]);
            }
        }
    }
    
    cout << ans;
}
