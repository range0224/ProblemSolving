#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[200010];
long long prefix[1000010];
long long suffix[1000010];

long long check(int idx, int a, int b)
{
    if(idx < 0 || idx > 1000000) return 1LL << 60;
    
    return a * prefix[idx] + b * suffix[idx];
}

int main()
{
    int q;
    int i;
    int a, b;
    int s, e;
    int mid;
    int idx;
    long long ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    
    idx = 0;
    for(i = 0; i <= 1000000; i++)
    {
        if(i != 0) prefix[i] = prefix[i - 1] + idx;
        
        while(idx < n && arr[idx] == i) idx++;
    }
    
    idx = n - 1;
    for(i = 1000000; i >= 0; i--)
    {
        suffix[i] = suffix[i + 1] + n - idx - 1;
        
        while(idx >= 0 && arr[idx] == i) idx--;
    }
    
    cin >> q;
    while(q--)
    {
        cin >> a >> b;

        s = 0;
        e = 1000000;
        ans = 1LL << 60;
        while(s <= e)
        {
            mid = (s + e) / 2;

            ans = min(ans, check(mid, a, b));

            if(check(mid, a, b) > check(mid + 1, a, b)) s = mid + 1;
            else e = mid - 1;
        }

        cout << ans << '\n';
    }
}
