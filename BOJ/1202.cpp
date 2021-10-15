#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int n, m;
vector<pair<int, int>> v;
vector<int> tv;

int main()
{
    int i;
    int a, b;
    int idx;
    priority_queue<int> pq;
    long long ans = 0;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> a >> b;
        
        v.push_back(make_pair(a, b));
    }
    for(i = 0; i < m; i++)
    {
        cin >> a;
        
        tv.push_back(a);
    }
    
    sort(v.begin(), v.end());
    sort(tv.begin(), tv.end());
    
    idx = 0;
    for(i = 0; i < tv.size(); i++)
    {
        while(idx < v.size() && v[idx].first <= tv[i])
        {
            pq.push(v[idx].second);
            idx++;
        }
        
        if(!pq.empty())
        {
            ans += pq.top();
            pq.pop();
        }
    }
    
    cout << ans;
}
