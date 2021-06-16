#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int arr[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
vector<int> tree[SIZE];
vector<long long> prefix[SIZE];
int cnt;

void make_tree()
{
	int i;
	int a, b;

	for (i = len - 1; i >= 1; i--)
	{
		a = 0;
		b = 0;

		while (a < tree[2 * i].size() && b < tree[2 * i + 1].size())
		{
			if (tree[2 * i][a] < tree[2 * i + 1][b]) tree[i].push_back(tree[2 * i][a++]);
			else tree[i].push_back(tree[2 * i + 1][b++]);
		}
		while (a < tree[2 * i].size()) tree[i].push_back(tree[2 * i][a++]);
		while (b < tree[2 * i + 1].size()) tree[i].push_back(tree[2 * i + 1][b++]);

		if (tree[i].empty()) continue;

		prefix[i].push_back(tree[i][0]);
		for (a = 1; a < tree[i].size(); a++)
		{
			prefix[i].push_back(prefix[i][a - 1] + tree[i][a]);
		}
	}
}

long long get(int idx, int s, int e, int ts, int te, int l, int r)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te)
	{
		ts = tree[idx].size();
		te = -1;

		s = 0;
		e = tree[idx].size() - 1;
		while (s <= e)
		{
			mid = (s + e) / 2;

			if (tree[idx][mid] >= l)
			{
				ts = mid;
				e = mid - 1;
			}
			else s = mid + 1;
		}

		s = 0;
		e = tree[idx].size() - 1;
		while(s <= e)
		{
			mid = (s + e) / 2;

			if (tree[idx][mid] <= r)
			{
				te = mid;
				s = mid + 1;
			}
			else e = mid - 1;
		}

		if (te >= ts)
		{
			if (ts == 0) return prefix[idx][te];
			else return prefix[idx][te] - prefix[idx][ts - 1];
		}
		return 0;
	}

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te, l, r) + get(2 * idx + 1, mid + 1, e, ts, te, l, r);
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
	int a, b, c, d;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 1; i <= n; i++)
	{
		tree[in[i] + len].push_back(arr[i]);
		prefix[in[i] + len].push_back(arr[i]);
	}

	make_tree();

	while (q--)
	{
		cin >> a >> b >> c >> d;

		ans = 0;
		while (top[a] != top[b])
		{
			if (depth[top[a]] < depth[top[b]]) swap(a, b);

			ans += get(1, 0, len - 1, in[top[a]], in[a], c, d);
			a = par[top[a]];
		}
		if (depth[a] > depth[b]) swap(a, b);

		ans += get(1, 0, len - 1, in[a], in[b], c, d);

		cout << ans << '\n';
	}
}
