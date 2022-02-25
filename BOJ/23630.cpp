#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[1000010];

int main()
{
    int i, j;
    int ans;
    int cnt;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    ans = 0;
    for(i = 0; i < 20; i++)
    {
        cnt = 0;
        for(j = 0; j < n; j++)
        {
            if(arr[j] & (1 << i)) cnt++;
        }
        
        ans = max(ans, cnt);
    }
    
    cout << ans;
}
