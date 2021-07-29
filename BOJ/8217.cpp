#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

const int SIZE = 1 << 20;
const int len = 1 << 19;
int n, m;
int arr[300010];
vector<int> v[300010];
vector<pair<pair<int, int>, int>> query;
vector<pair<int, int>> tv;
long long tree[SIZE];
int s[300010];
int e[300010];
int ans[300010];

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

int main()
{
    int q;
    int i, j;
    int a, b, c;
    int idx;
    long long sum;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 1; i <= m; i++)
    {
        cin >> a;
        
        v[a].push_back(i);
    }
    for(i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cin >> q;
    for(i = 0; i < q; i++)
    {
        cin >> a >> b >> c;
        
        query.push_back(make_pair(make_pair(a, b), c));
    }
    
    for(i = 1; i <= n; i++)
    {
        s[i] = 0;
        e[i] = q - 1;
        ans[i] = -1;
    }
    
    while(1)
    {
        tv.clear();
        
        for(i = 1; i <= n; i++)
        {
            if(s[i] > e[i]) continue;
            
            tv.push_back(make_pair((s[i] + e[i]) / 2, i));
        }
        
        if(tv.empty()) break;
        
        sort(tv.begin(), tv.end());
        
        memset(tree, 0, sizeof(tree));
        
        idx = 0;
        for(i = 0; i < tv.size(); i++)
        {
            while(idx < q && idx <= tv[i].first)
            {
                a = query[idx].first.first;
                b = query[idx].first.second;
                c = query[idx].second;
                
                if(a <= b)
                {
                    update(a, c);
                    update(b + 1, -c);
                }
                else
                {
                    update(a, c);
                    update(1, c);
                    update(b + 1, -c);
                }
                
                idx++;
            }
            
            sum = 0;
            for(j = 0; j < v[tv[i].second].size(); j++)
            {
                sum += get(1, 0, len - 1, 1, v[tv[i].second][j]);
                if(sum >= arr[tv[i].second]) break;
            }
            
            if(sum >= arr[tv[i].second])
            {
                ans[tv[i].second] = tv[i].first;
                e[tv[i].second] = tv[i].first - 1;
            }
            else s[tv[i].second] = tv[i].first + 1;
        }
    }
    
    for(i = 1; i <= n; i++)
    {
        if(ans[i] == -1) cout << "NIE\n";
        else cout << ans[i] + 1 << '\n';
    }
}
