#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long arr[20010][3];

bool check(long long x)
{
    int i;
    long long cnt;
    
    cnt = 0;
    for(i = 0; i < n; i++)
    {
        if(x < arr[i][0]) continue;
        
        cnt += min((x - arr[i][0]) / arr[i][2], (arr[i][1] - arr[i][0]) / arr[i][2]) + 1;
    }
    
    return cnt % 2;
}

long long get_cnt(long long x)
{
    int i;
    long long cnt;
    
    cnt = 0;
    for(i = 0; i < n; i++)
    {
        if(x >= arr[i][0] && x <= arr[i][1] && (x - arr[i][0]) % arr[i][2] == 0) cnt++;
    }
    
    return cnt;
}

int main()
{
    int i;
    long long s, e;
    long long mid;
    long long ans;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }
    
    s = 1;
    e = 2200000000LL;
    ans = 0;
    while(s <= e)
    {
        mid = (s + e) / 2;
        
        if(check(mid))
        {
            ans = mid;
            e = mid - 1;
        }
        else s = mid + 1;
    }
    
    if(ans == 0) cout << "NOTHING";
    else cout << ans << ' ' << get_cnt(ans);
}
