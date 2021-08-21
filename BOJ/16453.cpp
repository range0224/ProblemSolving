#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
vector<int> input[MAXV];
vector<int> v[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
bool visited[MAXV];
int tree[SIZE];
int lazy[SIZE];
int cnt = 1;

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += lazy[idx] * (e - s + 1);
	lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = value;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);

	tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < input[cur].size(); i++)
	{
		if (visited[input[cur][i]]) continue;

		v[cur].push_back(input[cur][i]);
		dfs(input[cur][i]);
	}
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
}

void update_query(int a, int b, int value)
{
	while (top[a] != top[b])
	{
		if (depth[top[a]] < depth[top[b]]) swap(a, b);

		update(1, 0, len - 1, in[top[a]], in[a], value);

		a = par[top[a]];
	}

	if (depth[a] > depth[b]) swap(a, b);

	update(1, 0, len - 1, in[a], in[b], value);
}

int get_query(int a, int b)
{
	int ret = 0;

	while (top[a] != top[b])
	{
		if (depth[top[a]] < depth[top[b]]) swap(a, b);

		ret += get(1, 0, len - 1, in[top[a]], in[a]);

		a = par[top[a]];
	}

	if (depth[a] > depth[b]) swap(a, b);

	ret += get(1, 0, len - 1, in[a], in[b]);

	return ret;
}

int main()
{
	int q;
	int i;
	int a, b, c, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	while (q--)
	{
		cin >> a >> b >> c >> d;

		update_query(a, b, 1);

		cout << get_query(c, d) << '\n';

		update_query(a, b, -1);
	}
}
