#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

typedef struct point_t
{
    long long x, y;
    int c;
    point_t(){}
    point_t(long long x, long long y, int c)
    {
        this->x = x;
        this->y = y;
        this->c = c;
    }
    bool operator<(const point_t &p) const
    {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator==(const point_t &p) const
    {
        return tie(x, y) == tie(p.x, p.y);
    }
}point;

typedef struct line_t
{
    int x, y;
    long long dx, dy;
    
    line_t(){}
    line_t(int x, int y, const point &p1, const point &p2)
    {
        this->x = x;
        this->y = y;
        this->dx = p2.x - p1.x;
        this->dy = p2.y - p1.y;
    }
    
    bool operator<(const line_t &l) const
    {
        long long lft = dy * l.dx;
        long long rgt = dx * l.dy;
        return tie(lft, x, y) < tie(rgt, l.x, l.y);
    }
    
    bool operator==(const line_t &l) const
    {
        return dy * l.dx == dx * l.dy;
    }
}line;

const int SIZE = 1 << 11;
const int len = 1 << 10;
int n;
int pos[1010];
int color[1010];
point arr[1010];
vector<line> v;
pair<pair<int, int>, pair<int, int>> tree[SIZE];

pair<pair<int, int>, pair<int, int>> get_node(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
    pair<pair<int, int>, pair<int, int>> ret;
    
    ret.first.first = max(max(a.first.first, b.first.first), a.second.second + b.second.first);
    ret.first.second = a.first.second + b.first.second;
    ret.second.first = max(a.second.first, a.first.second + b.second.first);
    ret.second.second = max(b.second.second, b.first.second + a.second.second);
    
    return ret;
}

void update(int idx, int v)
{
    idx += len;
    tree[idx] = make_pair(make_pair(v, v), make_pair(v, v));
    idx /= 2;
    while(idx >= 1)
    {
        tree[idx] = get_node(tree[2 * idx], tree[2 * idx + 1]);
        idx /= 2;
    }
}

pair<pair<int, int>, pair<int, int>> get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return make_pair(make_pair(-(1LL << 50), 0), make_pair(-(1LL << 50), -(1LL << 50)));
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return get_node(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
    int i, j;
    int a, b;
    char c;
    int mx;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    
    for(i = 0; i < n; i++)
    {
        cin >> a >> b >> c;
        
        if(c == 'R') color[i] = 1;
        else color[i] = -10000;
        
        arr[i] = point(a, b, color[i]);
    }
    
    sort(arr, arr + n);
    
    for(i = 0; i < n; i++) pos[i] = i;
    
    v.clear();
    for(i = 0; i < n; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            v.push_back(line(i, j, arr[i], arr[j]));
        }
    }
    sort(v.begin(), v.end());
    
    for(i = 0; i < n; i++)
    {
        update(i, arr[i].c);
    }
    
    mx = 0;
    idx = 0;
    for(i = 0; i < v.size(); i = idx)
    {
        while(idx < v.size() && v[i] == v[idx]) idx++;
        
        for(j = i; j < idx; j++)
        {
            a = v[j].x;
            b = v[j].y;
            
            swap(pos[a], pos[b]);
            swap(arr[pos[a]], arr[pos[b]]);
            
            update(pos[a], arr[pos[a]].c);
            update(pos[b], arr[pos[b]].c);
            
            mx = max(mx, get(1, 0, len - 1, 0, n - 1).first.first);
        }
    }
    
    cout << mx;
}
