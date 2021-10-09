#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[500010];
int ans[500010];

int main()
{
    int i;
    int s, e;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    sort(arr, arr + n);
    
    if(arr[0] >= 0)
    {
        s = 0;
        e = n - 1;
        idx = 0;
        while(s < e)
        {
            ans[s++] = arr[idx++];
            ans[e--] = arr[idx++];
        }
        if(s == e) ans[s] = arr[idx];
    }
    else
    {
        for(i = 0; i < n; i++)
        {
            if(arr[i] >= 0) break;
        }
        
        s = 0;
        e = i - 1;
        idx = i - 1;
        while(s < e)
        {
            ans[e--] = arr[idx--];
            ans[s++] = arr[idx--];
        }
        if(s == e) ans[s] = arr[idx];
        
        s = i;
        e = n - 1;
        idx = i;
        while(s < e)
        {
            ans[s++] = arr[idx++];
            ans[e--] = arr[idx++];
        }
        if(s == e) ans[s] = arr[idx];
    }
    
    for(i = 0; i < n; i++)
    {
        cout << ans[i] << ' ';
    }
}
