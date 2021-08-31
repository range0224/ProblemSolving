#include<iostream>
#include<vector>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
vector<int> v[100010];
int in[100010], out[100010];
int tree[SIZE];
int cnt;

void update(int idx, int value)
{
    idx += len;
    while(idx >= 1)
    {
        tree[idx] += value;
        idx /= 2;
    }
}

int get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

void dfs(int cur)
{
    int i;
    
    in[cur] = cnt++;
    for(i = 0; i < v[cur].size(); i++)
    {
        dfs(v[cur][i]);
    }
    out[cur] = cnt - 1;
}

int main()
{
    int q;
    int i;
    int a, b, c;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    cin >> a;
    for(i = 2; i <= n; i++)
    {
        cin >> a;
        
        v[a].push_back(i);
    }
    
    dfs(1);
    
    while(q--)
    {
        cin >> a;
        
        if(a == 1)
        {
            cin >> b >> c;
            
            update(in[b], c);
        }
        else
        {
            cin >> b;
            
            cout << get(1, 0, len - 1, in[b], out[b]) << '\n';
        }
    }
}
