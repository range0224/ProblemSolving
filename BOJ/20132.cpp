#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const long long INF = 1LL << 60;
const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n, m;
int sz[MAXV], pars[MAXV], depth[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
vector<int> tv[MAXV];
vector<pair<pair<int, int>, int>> v;
int par[MAXV];
bool connected[300010];
bool visited[MAXV];
int cnt;
int tree[2][SIZE];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.second < b.second;
}

void update(int idx, int value, int *tree)
{
    idx += len;
    tree[idx] = value;
    idx /= 2;
    while(idx >= 1)
    {
        tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
        idx /= 2;
    }
}

int get(int idx, int s, int e, int ts, int te, int *tree)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return max(get(2 * idx, s, mid, ts, te, tree), get(2 * idx + 1, mid + 1, e, ts, te, tree));
}

int find(int x)
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    par[a] = b;
}

void dfs(int cur)
{
    int i;
    
    visited[cur] = true;
    for(i = 0; i < input[cur].size(); i++)
    {
        if(visited[input[cur][i]]) continue;
        
        tv[cur].push_back(input[cur][i]);
        dfs(input[cur][i]);
    }
}

void dfs1(int cur)
{
    int i;
    
    sz[cur] = 1;
    for(i = 0; i < tv[cur].size(); i++)
    {
        pars[tv[cur][i]] = cur;
        depth[tv[cur][i]] = depth[cur] + 1;
        dfs1(tv[cur][i]);
        sz[cur] += sz[tv[cur][i]];
        
        if(sz[tv[cur][i]] > sz[tv[cur][0]]) swap(tv[cur][i], tv[cur][0]);
    }
}

void dfs2(int cur)
{
    int i;
    
    in[cur] = cnt++;
    for(i = 0; i < tv[cur].size(); i++)
    {
        if(i == 0) top[tv[cur][i]] = top[cur];
        else top[tv[cur][i]] = tv[cur][i];
        
        dfs2(tv[cur][i]);
    }
}

int main()
{
    int i;
    int a, b, c;
    long long sum;
    int cnt;
    long long mn = INF;
    int mx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        
        v.push_back(make_pair(make_pair(a, b), c));
    }
    
    for(i = 1; i <= n; i++) par[i] = i;
    
    sort(v.begin(), v.end(), comp);
    
    sum = 0;
    cnt = 0;
    for(i = 0; i < v.size(); i++)
    {
        if(find(v[i].first.first) == find(v[i].first.second)) continue;
        
        union_(v[i].first.first, v[i].first.second);
        sum += v[i].second;
        cnt++;
        connected[i] = true;
        input[v[i].first.first].push_back(v[i].first.second);
        input[v[i].first.second].push_back(v[i].first.first);
    }
    
    if(cnt < n - 1)
    {
        cout << -1 << ' ' << -1;
        return 0;
    }
    
    dfs(1);
    dfs1(1);
    dfs2(1);
    
    for(i = 0; i < v.size(); i++)
    {
        a = v[i].first.first;
        b = v[i].first.second;
        c = v[i].second;
        
        if(connected[i])
        {
            if(pars[a] == b) update(in[a], c, tree[c % 2]);
            else update(in[b], c, tree[c % 2]);
            
            continue;
        }
        
        while(top[a] != top[b])
        {
            if(depth[top[a]] < depth[top[b]]) swap(a, b);
            
            mx = get(1, 0, len - 1, in[top[a]], in[a], tree[!(c % 2)]);
            a = pars[top[a]];
            
            if(mx != 0) mn = min(mn, sum + c - mx);
        }
        
        if(a == b) continue;
        
        if(depth[a] > depth[b]) swap(a, b);
        
        mx = get(1, 0, len - 1, in[a] + 1, in[b], tree[!(c % 2)]);
        
        if(mx != 0) mn = min(mn, sum + c - mx);
    }
    
    if(sum % 2 == 1)
    {
        cout << sum << ' ';
        if(mn == INF) cout << -1;
        else cout << mn;
    }
    else
    {
        if(mn == INF) cout << -1 << ' ';
        else cout << mn << ' ';
        cout << sum;
    }
}
