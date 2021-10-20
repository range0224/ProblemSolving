#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int n, m;
int a[200010];
int b[200010];
priority_queue<pair<int, int>> pq;

int main()
{
    int i;
    long long ans;
    int x, y;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> m >> n;
    for(i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for(i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    
    ans = 0;
    for(i = 0; i < n; i++)
    {
        ans += a[i];
        pq.push(make_pair(min(b[i], 100 - a[i]), a[i]));
    }
    
    m *= 24;
    while(m--)
    {
        x = pq.top().first;
        y = pq.top().second;
        pq.pop();
        
        ans += x;
        y += x;
        pq.push(make_pair(min(x, 100 - y), y));
    }
    
    cout << ans;
}
