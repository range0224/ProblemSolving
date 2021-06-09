#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int SIZE = 1 << 19;
const int len = 1 << 18;
const int MAXV = 200010;
int n;
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV], out[MAXV];
vector<int> v[MAXV];
int cnt;
int tree[SIZE];
void update(int idx, int value)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx] += value;
		idx /= 2;
	}
}
int get(int idx, int s, int e, int ts, int te)
{
	int mid;
	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];
	mid = (s + e) / 2;
	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}
void dfs1(int cur)
{
	int i;
	sz[cur] = 1;
	for (i = 0; i < v[cur].size(); i++)
	{
		depth[v[cur][i]] = depth[cur] + 1;
		par[v[cur][i]] = cur;
		dfs1(v[cur][i]);
		sz[cur] += sz[v[cur][i]];
		if (sz[v[cur][i]] > sz[v[cur][0]]) swap(v[cur][i], v[cur][0]);
	}
}
void dfs2(int cur)
{
	int i;
	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (i == 0) top[v[cur][i]] = top[cur];
		else top[v[cur][i]] = v[cur][i];
		dfs2(v[cur][i]);
	}
	out[cur] = cnt;
}
bool query(int a, int b)
{
	while (top[a] != top[b])
	{
		if (depth[top[a]] < depth[top[b]]) swap(a, b);
		if (get(1, 0, len - 1, in[top[a]], in[a])) return false;
		a = par[top[a]];
	}
	if (a == b) return true;
	if (depth[a] > depth[b]) swap(a, b);
	if (get(1, 0, len - 1, in[a] + 1, in[b])) return false;
	else return true;
}
int main()
{
	int q;
	int i;
	int a, b, c;
	bool ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
	cin >> n >> q;
	for (i = 2; i <= n; i++)
	{
		cin >> a;
		v[a].push_back(i);
	}
    
	dfs1(1);
	dfs2(1);
    
	while (q--)
	{
		cin >> a >> b >> c;
		ans = query(a, b);
		if (ans) cout << "YES\n";
		else cout << "NO\n";
		if (c == 1)
		{
			if (ans) update(in[a], 1);
			else update(in[b], 1);
		}
	}
}
