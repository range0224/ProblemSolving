#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int n;
int x[5010];
int y[5010];
vector<pair<int, int>> v;
int sx, sy, ex, ey;
int suffix[5010];

int get_dist(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

bool comp(pair<int, int> a, pair<int, int> b)
{
    return get_dist(sx, sy, a.first, a.second) < get_dist(sx, sy, b.first, b.second);
}

int main()
{
    int i, j;
    int prefix;
    double ans;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> x[i] >> y[i];
        
        v.push_back(make_pair(x[i], y[i]));
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(get_dist(sx, sy, ex, ey) < get_dist(x[i], y[i], x[j], y[j]))
            {
                sx = x[i];
                sy = y[i];
                ex = x[j];
                ey = y[j];
            }
        }
    }
    
    sort(v.begin(), v.end(), comp);
    for(i = n - 1; i >= 0; i--)
    {
        suffix[i] = suffix[i + 1];
        for(j = n - 1; j > i; j--)
        {
            suffix[i] = max(suffix[i], get_dist(v[i].first, v[i].second, v[j].first, v[j].second));
        }
    }
    
    ans = 1000000000;
    prefix = 0;
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < i; j++)
        {
            prefix = max(prefix, get_dist(v[i].first, v[i].second, v[j].first, v[j].second));
        }
        
        ans = min(ans, sqrt(prefix) + sqrt(suffix[i + 1]));
    }
    
    printf("%.9lf", ans);
}
