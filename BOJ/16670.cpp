#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 22;
const int len =  1 << 21;
pair<long long, long long> tree[SIZE];
vector<pair<int, int>> v;
long long ans;

pair<long long, long long> merge(pair<long long, long long> a, pair<long long, long long> b)
{
    return make_pair(a.first + b.first, max(b.second, a.second + b.first));
}

void init(int idx, int s, int e)
{
    int mid;
    
    if(s == e)
    {
        tree[idx].first = 0;
        tree[idx].second = s;
        return;
    }
    
    mid = (s + e) / 2;
    
    init(2 * idx, s, mid);
    init(2 * idx + 1, mid + 1, e);
    tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

void update(int idx, int value)
{
    idx += len;
    tree[idx].first += value;
    tree[idx].second += value;
    idx /= 2;
    while(idx >= 1)
    {
        tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
        idx /= 2;
    }
}

void get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(e <= te)
    {
        ans = max(ans + tree[idx].first, tree[idx].second);
        return;
    }
    
    mid = (s + e) / 2;
    
    get(2 * idx, s, mid, ts, te);
    if(mid + 1 <= te) get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
    int q;
    char a;
    int b, c;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    init(1, 0, len - 1);
    
    cin >> q;
    while(q--)
    {
        cin >> a;
        
        if(a == '+')
        {
            cin >> b >> c;
            
            v.push_back(make_pair(b, c));
            
            update(b, c);
        }
        else if(a == '-')
        {
            cin >> b;
            
            v.push_back(make_pair(b, 0));
            
            update(v[b - 1].first, -v[b - 1].second);
        }
        else
        {
            cin >> b;
            
            v.push_back(make_pair(b, 0));
            
            ans = 0;
            get(1, 0, len - 1, b, b);
            
            cout << max(ans - b, 0LL) << '\n';
        }
    }
}
