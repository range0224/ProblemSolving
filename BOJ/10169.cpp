#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 1 << 30;
const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n, m;
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV];
vector<pair<pair<int, int>, pair<int, int>>> tv;
vector<int> input[MAXV];
vector<int> v[MAXV];
int uf_par[MAXV];
bool visited[MAXV];
bool used[300010];
int cnt;
int tree[SIZE];
int lazy[SIZE];

bool comp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
	return a.second.first < b.second.first;
}

bool comp2(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
	return a.second.second < b.second.second;
}

int find(int x)
{
	if (uf_par[x] == x) return x;
	else return uf_par[x] = find(uf_par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	uf_par[a] = b;
}

void propagate(int idx)
{
	if (idx < len)
	{
		lazy[2 * idx] = min(lazy[2 * idx], lazy[idx]);
		lazy[2 * idx + 1] = min(lazy[2 * idx + 1], lazy[idx]);
	}
	tree[idx] = min(tree[idx], lazy[idx]);
	lazy[idx] = INF;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = value;
		propagate(idx);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);

	tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx);

	if (s > te || e < ts) return INF;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return min(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
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
		par[v[cur][i]] = cur;
		depth[v[cur][i]] = depth[cur] + 1;
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

int main()
{
	int i;
	int a, b, c;
	long long ans;
	int cnt;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		tv.push_back(make_pair(make_pair(a, b), make_pair(c, i)));
	}

	sort(tv.begin(), tv.end(), comp);

	for (i = 1; i <= n; i++) uf_par[i] = i;

	ans = 0;
	cnt = 0;
	for (i = 0; i < tv.size(); i++)
	{
		if (find(tv[i].first.first) == find(tv[i].first.second)) continue;

		union_(tv[i].first.first, tv[i].first.second);
		ans += tv[i].second.first;
		input[tv[i].first.first].push_back(tv[i].first.second);
		input[tv[i].first.second].push_back(tv[i].first.first);
		used[tv[i].second.second] = true;
		cnt++;
	}

	if (cnt < n - 1)
	{
		for (i = 0; i < tv.size(); i++)
		{
			cout << -1 << '\n';
		}
		return 0;
	}

	sort(tv.begin(), tv.end(), comp2);

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = SIZE - 1; i >= 1; i--)
	{
		tree[i] = INF;
		lazy[i] = INF;
	}

	for (i = 0; i < tv.size(); i++)
	{
		if (used[i]) continue;

		a = tv[i].first.first;
		b = tv[i].first.second;
		c = tv[i].second.first;

		while (top[a] != top[b])
		{
			if (depth[top[a]] < depth[top[b]]) swap(a, b);

			update(1, 0, len - 1, in[top[a]], in[a], c);
			a = par[top[a]];
		}

		if (a == b) continue;

		if (depth[a] > depth[b]) swap(a, b);

		update(1, 0, len - 1, in[a] + 1, in[b], c);
	}

	for (i = 0; i < tv.size(); i++)
	{
		if (!used[i])
		{
			cout << ans << '\n';
			continue;
		}

		a = tv[i].first.first;
		b = tv[i].first.second;
		c = tv[i].second.first;

		x = INF;
		while (top[a] != top[b])
		{
			if (depth[top[a]] < depth[top[b]]) swap(a, b);

			x = min(x, get(1, 0, len - 1, in[top[a]], in[a]));
			a = par[top[a]];
		}

		if (a != b)
		{
			if (depth[a] > depth[b]) swap(a, b);

			x = min(x, get(1, 0, len - 1, in[a] + 1, in[b]));
		}

		if (x == INF) cout << -1 << '\n';
		else cout << ans + x - c << '\n';
	}
}
