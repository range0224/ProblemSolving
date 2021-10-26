#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
int arr[4][1010];
vector<int> v[2];

int main()
{
    int t;
    int i, j;
    int s, e;
    int ans;
    int gap;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> t;
    while(t--)
    {
        cin >> m >> n;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < n; j++)
            {
                cin >> arr[i][j];
            }
        }
        
        v[0].clear();
        v[1].clear();
        
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                v[0].push_back(arr[0][i] + arr[1][j]);
                v[1].push_back(arr[2][i] + arr[3][j]);
            }
        }
        
        sort(v[0].begin(), v[0].end());
        sort(v[1].begin(), v[1].end());
        
        ans = 100000000;
        s = 0;
        e = v[1].size() - 1;
        while(s < v[0].size() && e >= 0)
        {
            gap = abs(m - (v[0][s] + v[1][e]));
            
            if(abs(m - ans) > gap || (abs(m - ans) == gap && v[0][s] + v[1][e] < ans)) ans = v[0][s] + v[1][e];
            
            if(v[0][s] + v[1][e] > m) e--;
            else s++;
        }
        
        cout << ans << '\n';
    }
}
