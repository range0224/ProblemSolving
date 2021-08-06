#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int MAXV = 100010;
int n, m;
int arr[100010];
vector<int> input[MAXV];
vector<pair<int, int>> nodes;
vector<int> v[MAXV];
vector<pair<int, pair<int, int>>> query;
vector<pair<int, int>> tv;
map<int, int> mp;
int rmp[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
bool visited[MAXV];
int tree[MAXV];
int s[MAXV];
int e[MAXV];
int ans[MAXV];
int cnt = 1;

void update(int idx)
{
	while (idx <= n)
	{
		tree[idx]++;
		idx += (idx & (-idx));
	}
}

int get(int idx)
{
	int ret = 0;

	if (idx == 0) return 0;

	while (idx >= 1)
	{
		ret += tree[idx];
		idx -= (idx & (-idx));
	}

	return ret;
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
	int i;
	int a, b, c;
	int sum;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		nodes.push_back(make_pair(arr[i], i));
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		query.push_back(make_pair(c, make_pair(a, b)));

		s[i] = 0;
		e[i] = n - 1;
	}

	sort(nodes.begin(), nodes.end());

	idx = 1;
	mp[nodes[0].first] = 0;
	rmp[0] = nodes[0].first;
	for (i = 1; i < nodes.size(); i++)
	{
		if (nodes[i].first == nodes[i - 1].first) continue;

		mp[nodes[i].first] = idx;
		rmp[idx] = nodes[i].first;
		idx++;
	}

	for (i = 0; i < nodes.size(); i++) nodes[i].first = mp[nodes[i].first];

	dfs(1);
	dfs1(1);
	dfs2(1);

	while (1)
	{
		tv.clear();

		for (i = 0; i < m; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		memset(tree, 0, sizeof(tree));

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < n && nodes[idx].first <= tv[i].first)
			{
				update(in[nodes[idx].second]);
				idx++;
			}

			sum = 0;
			a = query[tv[i].second].second.first;
			b = query[tv[i].second].second.second;
			while (top[a] != top[b])
			{
				if (depth[top[a]] < depth[top[b]]) swap(a, b);

				sum += get(in[a]) - get(in[top[a]] - 1);
				a = par[top[a]];
			}

			if (depth[a] > depth[b]) swap(a, b);

			sum += get(in[b]) - get(in[a] - 1);

			if (sum >= query[tv[i].second].first)
			{
				ans[tv[i].second] = tv[i].first;
				e[tv[i].second] = tv[i].first - 1;
			}
			else s[tv[i].second] = tv[i].first + 1;
		}
	}

	for (i = 0; i < m; i++)
	{
		cout << rmp[ans[i]] << '\n';
	}
}
