#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[100010];

bool check(int x)
{
    int i;
    int cnt = 0;
    
    for(i = n - 1; i >= n - x; i--)
    {
        if(arr[i] == x - 1) cnt++;
        else if(arr[i] < x - 1) return false;
    }
    
    return cnt <= m;
}

int main()
{
    int i;
    int s, e;
    int mid;
    int ans;
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    sort(arr, arr + n);
    
    s = 0;
    e = n;
    while(s <= e)
    {
        mid = (s + e) / 2;
        
        if(check(mid))
        {
            ans = mid;
            s = mid + 1;
        }
        else e = mid - 1;
    }
    
    cout << ans;
}
