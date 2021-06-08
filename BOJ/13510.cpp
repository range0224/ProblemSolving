#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int arr[100010];
vector<pair<int, int>> edge;
vector<pair<int, int>> input[100010];
vector<int> v[100010];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV], out[MAXV];
int tree[SIZE];
int cnt;
bool visited[MAXV];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < input[cur].size(); i++)
	{
		if (visited[input[cur][i].first])
		{
			arr[cur] = input[cur][i].second;
			continue;
		}

		v[cur].push_back(input[cur][i].first);
		dfs(input[cur][i].first);
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
	out[cur] = cnt;
}

int query(int a, int b)
{
	int ret = 0;

	while (top[a] != top[b])
	{
		if (depth[top[a]] < depth[top[b]]) swap(a, b);

		ret = max(ret, get(1, 0, len - 1, in[top[a]], in[a]));
		a = par[top[a]];
	}

	if (a == b) return ret;

	if (depth[a] > depth[b]) swap(a, b);
	ret = max(ret, get(1, 0, len - 1, in[a] + 1, in[b]));

	return ret;
}

int main()
{
	int i;
	int a, b, c;
	int q;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b >> c;

		input[a].push_back(make_pair(b, c));
		input[b].push_back(make_pair(a, c));

		edge.push_back(make_pair(a, b));
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 2; i <= n; i++)
	{
		update(in[i], arr[i]);
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c;

		if (a == 1)
		{
			a = edge[b - 1].first;
			b = edge[b - 1].second;

			if (par[a] == b) update(in[a], c);
			else update(in[b], c);
		}
		else
		{
			cout << query(b, c) << '\n';
		}
	}
}
