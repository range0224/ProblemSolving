#include<iostream>
using namespace std;

int n, m;
long long cnt1[10010];
long long cnt2[10010];

int main()
{
    int i, j;
    int a, b;
    long long ans;
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> a >> b;
        
        cnt1[a]++;
        cnt2[b]++;
    }
    
    ans = cnt1[0] * cnt1[0];
    cout << ans << '\n';
    for(i = 1; i <= 2 * m; i++)
    {
        for(j = 0; j <= i; j++)
        {
            ans += cnt1[j] * cnt1[i - j];
        }
        
        for(j = 0; j <= i - 1; j++)
        {
            ans -= cnt2[j] * cnt2[i - 1 - j];
        }
        
        cout << ans << '\n';
    }
}
