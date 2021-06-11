#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 30010;
int n;
int arr[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV], out[MAXV];
vector<pair<string, pair<int,int>>> query;
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
long long tree[SIZE];
int uf[MAXV];

void update(int idx, int value)
{
    idx += len;
    tree[idx] = value;
    idx /= 2;
    while(idx >= 1)
    {
        tree[idx] = tree[2*idx] + tree[2*idx+1];
        idx /= 2;
    }
}

long long get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return get(2*idx,s,mid,ts,te) + get(2*idx+1,mid+1,e,ts,te);
}

int find(int x)
{
    if(uf[x] == x) return x;
    else return uf[x] = find(uf[x]);
}

void union_(int x, int y)
{
    x = find(x);
    y = find(y);
    
    uf[x] = y;
}

void dfs(int cur)
{
    int i;
    
    visited[cur] = true;
    for(i=0;i<input[cur].size();i++)
    {
        if(visited[input[cur][i]]) continue;
        
        v[cur].push_back(input[cur][i]);
        dfs(input[cur][i]);
    }
}

void dfs1(int cur)
{
    int i;
    
    sz[cur] = 1;
    for(i=0;i<v[cur].size();i++)
    {
        depth[v[cur][i]] = depth[cur] + 1;
        par[v[cur][i]] = cur;
        dfs1(v[cur][i]);
        sz[cur] += sz[v[cur][i]];
        
        if(sz[v[cur][i]] > sz[v[cur][0]]) swap(v[cur][i], v[cur][0]);
    }
}

void dfs2(int cur)
{
    int i;
    
    in[cur] = cnt++;
    for(i=0;i<v[cur].size();i++)
    {
        if(i == 0) top[v[cur][i]] = top[cur];
        else top[v[cur][i]] = v[cur][i];
        
        dfs2(v[cur][i]);
    }
    out[cur] = cnt;
}

int main()
{
    int i;
    int q;
    string a;
    int b, c;
    long long ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i=1;i<=n;i++)
    {
        cin >> arr[i];
        
        uf[i] = i;
    }
    cin >> q;
    while(q--)
    {
        cin >> a >> b >> c;
        
        query.push_back(make_pair(a, make_pair(b,c)));
        
        if(a[0] == 'b')
        {
            if(find(b) == find(c)) continue;
            
            input[b].push_back(c);
            input[c].push_back(b);
            union_(b, c);
        }
    }
    
    for(i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            dfs(i);
            dfs1(i);
            dfs2(i);
        }
    }
    
    for(i=1;i<=n;i++)
    {
        update(in[i], arr[i]);
        uf[i] = i;
    }
    
    for(i=0;i<query.size();i++)
    {
        a = query[i].first;
        b = query[i].second.first;
        c = query[i].second.second;
        
        if(a[0] == 'b')
        {
            if(find(b) == find(c)) cout << "no\n";
            else
            {
                cout << "yes\n";
                union_(b, c);
            }
        }
        else if(a[0] == 'p')
        {
            update(in[b], c);
        }
        else
        {
            if(find(b) != find(c))
            {
                cout << "impossible\n";
                continue;
            }
            
            ans = 0;
            while(top[b] != top[c])
            {
                if(depth[top[b]] < depth[top[c]]) swap(b, c);
                
                ans += get(1, 0, len - 1, in[top[b]], in[b]);
                b = par[top[b]];
            }
            
            if(depth[b] > depth[c]) swap(b, c);
            
            ans += get(1, 0, len - 1, in[b], in[c]);
            
            cout << ans << '\n';
        }
    }
}
