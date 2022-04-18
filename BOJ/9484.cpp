#include<iostream>
#include<vector>
#include<tuple>
#include<algorithm>
using namespace std;

typedef struct point_t
{
    long long x, y;
    point_t(){}
    point_t(int x, int y)
    {
        this->x = x;
        this->y = y;
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

int n;
int pos[2010];
point arr[2010];
vector<line> v;

long long get_area(point a, point b, point c)
{
    return abs((b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y));
}

int main()
{
    int i, j;
    int a, b;
    long long mn, mx;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    while(1)
    {
        cin >> n;
        
        if(!n) break;
        
        for(i = 0; i < n; i++)
        {
            cin >> a >> b;
            
            arr[i] = point(a, b);
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
        
        mn = 1LL << 60;
        mx = -(1LL << 60);
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
                
                if(pos[a] > pos[b]) swap(a, b);
                
                if(pos[a] >= 1)
                {
                    mn = min(mn, get_area(arr[pos[a]], arr[pos[b]], arr[pos[a] - 1]));
                    mx = max(mx, get_area(arr[pos[a]], arr[pos[b]], arr[0]));
                }
                if(pos[b] < n - 1)
                {
                    mn = min(mn, get_area(arr[pos[a]], arr[pos[b]], arr[pos[b] + 1]));
                    mx = max(mx, get_area(arr[pos[a]], arr[pos[b]], arr[n - 1]));
                }
            }
        }
        
        cout << mn / 2 << '.' << (mn % 2) * 5 << ' ';
        cout << mx / 2 << '.' << (mx % 2) * 5 << '\n';
    }
}
