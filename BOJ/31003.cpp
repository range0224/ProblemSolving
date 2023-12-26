#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int arr[3010];
bool v[3010][3010];
int cnt[3010];
vector<pair<int, int>> tv;
bool visited[3010];

int get_gcd(int a, int b)
{
    int temp;
    
    while(a % b)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    
    return b;
}

int main()
{
    int i, j, k;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(get_gcd(arr[i], arr[j]) != 1)
            {
                v[i][j] = true;
                v[j][i] = true;
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(v[i][j]) cnt[i]++;
        }
    }
    
    for(i = 0; i < n; i++) tv.push_back(make_pair(arr[i], i));
    
    sort(tv.begin(), tv.end());
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(visited[j]) continue;
            
            if(cnt[tv[j].second] == 0)
            {
                cout << tv[j].first << ' ';
                
                for(k = tv[j].second + 1; k < n; k++)
                {
                    if(v[k][tv[j].second]) cnt[k]--;
                }
                
                visited[j] = true;
                
                break;
            }
        }
    }
}
