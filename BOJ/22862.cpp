#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[1000010];

int main()
{
    int i;
    int s, e;
    int ans;
    int cnt;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    s = 0;
    e = 0;
    ans = 0;
    cnt = arr[0] % 2;
    while(e < n)
    {
        if(cnt <= m)
        {
            ans = max(ans, e - s + 1 - cnt);
            e++;
            cnt += arr[e] % 2;
        }
        else
        {
            cnt -= arr[s] % 2;
            s++;
        }
    }
    
    cout << ans;
}
