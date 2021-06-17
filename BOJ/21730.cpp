#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 19;
const int len = 1 << 18;
const int MAXV = 200010;
int n, m;
pair<int, int> arr[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
int tree[SIZE];
int lazy[SIZE];

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}

	if (s % 2 == 0) tree[idx] += lazy[idx];
	if (e % 2 == 1) tree[idx] -= lazy[idx];

	lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = 1;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te);
	update(2 * idx + 1, mid + 1, e, ts, te);

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

int main()
{
	int q;
	int i;
	int a, b, c;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> q;
	for (i = 1; i < n; i++)
	{
		cin >> a >> b;

		a = 2 * a - 1;
		b = 2 * b - 1;

		input[a].push_back(2 * i);
		input[2 * i].push_back(a);
		input[b].push_back(2 * i);
		input[2 * i].push_back(b);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 1; i <= m; i++)
	{
		cin >> arr[i].first >> arr[i].second;

		arr[i].first = 2 * arr[i].first - 1;
		arr[i].second = 2 * arr[i].second - 1;
	}

	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			b = 2 * b - 1;
			c = 2 * c - 1;

			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				update(1, 0, len - 1, in[top[b]], in[b]);
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			update(1, 0, len - 1, in[b], in[c]);
		}
		else
		{
			cin >> b;

			c = arr[b].second;
			b = arr[b].first;

			ans = 0;
			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				ans += get(1, 0, len - 1, in[top[b]], in[b]);
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			ans += get(1, 0, len - 1, in[b], in[c]);

			cout << ans << '\n';
		}
	}
}
