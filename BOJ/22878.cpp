#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int SIZE = 1 << 22;
const int len = 1 << 21;
int n;
long long a[1000010];
long long b[1000010];
vector<pair<long long, long long>> v;
vector<pair<long long, long long>> tv;
long long tree[SIZE];
long long tree2[SIZE];

bool comp(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}

bool comp2(pair<int, int> a, pair<int, int> b)
{
    if(a.second != b.second) return a.second < b.second;
    else return a.first < b.first;
}

void update(int idx, int value)
{
    idx += len;
    while(idx >= 1)
    {
        tree[idx] += value;
        idx /= 2;
    }
}

long long get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

void update2(int idx, long long value)
{
    idx += len;
    while(idx >= 1)
    {
        tree2[idx] += value;
        idx /= 2;
    }
}

long long get2(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree2[idx];
    
    mid = (s + e) / 2;
    
    return get2(2 * idx, s, mid, ts, te) + get2(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
    int i;
    long long sum;
    long long ans;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for(i = 1; i <= n; i++)
    {
        cin >> b[i];
    }
    
    for(i = 1; i <= n; i++)
    {
        v.push_back(make_pair(a[i], b[i]));
    }
    
    sort(v.begin(), v.end());
    
    ans = 0;
    sum = 0;
    for(i = 0; i < n; i++)
    {
        ans += 1LL * i * v[i].first - sum;
        sum += v[i].first;
    }
    
    for(i = 0; i < n; i++)
    {
        tv.push_back(make_pair(v[i].second, v[i].first - v[i].second + 1000000));
    }
    
    sort(tv.begin(), tv.end());
    
    idx = 0;
    for(i = 0; i < tv.size();)
    {
        idx = i;
        
        while(idx < tv.size() && tv[idx].first == tv[i].first)
        {
            ans -= get2(1, 0, len - 1, 0, tv[idx].second) * tv[idx].second - get(1, 0, len - 1, 0, tv[idx].second);
            idx++;
        }
        
        idx = i;
        
        while(idx < tv.size() && tv[idx].first == tv[i].first)
        {
            update(tv[idx].second, tv[idx].second);
            update2(tv[idx].second, 1);
            idx++;
        }
        
        i = idx;
    }
    
    memset(tree, 0, sizeof(tree));
    memset(tree2, 0, sizeof(tree2));
    
    tv.clear();
    for(i = 0; i < n; i++)
    {
        tv.push_back(make_pair(v[i].second, v[i].first + v[i].second));
    }
    
    sort(tv.begin(), tv.end(), comp);
    
    for(i = 0; i < tv.size();)
    {
        idx = i;
        while(idx < tv.size() && tv[idx].first == tv[i].first)
        {
            ans -= get2(1, 0, len - 1, 0, tv[idx].second) * tv[idx].second - get(1, 0, len - 1, 0, tv[idx].second);
            idx++;
        }
        
        idx = i;
        while(idx < tv.size() && tv[idx].first == tv[i].first)
        {
            update(tv[idx].second, tv[idx].second);
            update2(tv[idx].second, 1);
            idx++;
        }
        
        i = idx;
    }
    
    sort(v.begin(), v.end(), comp2);
    
    for(i = 0; i < v.size();)
    {
        idx = i;
        sum = 0;
        while(idx < v.size() && v[idx].second == v[i].second)
        {
            ans -= 1LL * (idx - i) * v[idx].first - sum;
            
            sum += v[idx].first;
            idx++;
        }
        
        i = idx;
    }
    
    cout << 2 * ans;
}
