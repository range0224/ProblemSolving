#include<iostream>
#include<algorithm>
using namespace std;

int n;
int x[100010];
int y[100010];

int main()
{
    int i;
    long long ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
    }
    
    sort(x, x + n);
    sort(y, y + n);
    
    ans = 0;
    for(i = 0; i < n; i++)
    {
        ans += abs(x[i] - x[n / 2]);
        ans += abs(y[i] - y[n / 2]);
    }
    
    cout << ans;
}
