#include<iostream>
#include<vector>
using namespace std;

const int MAXV = 500010;
const int SIZE = 1 << 20;
const int len = 1 << 19;
int n;
int arr[MAXV];
vector<int> v[MAXV];
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
int cnt = 1;
long long tree1[MAXV];
long long tree2[MAXV];
vector<int> nodes;

void update(int idx, long long value, long long* tree)
{
	while (idx <= n)
	{
		tree[idx] += value;
		idx += (idx & (-idx));
	}
}

long long get(int idx, long long* tree)
{
	long long ret = 0;

	while (idx >= 1)
	{
		ret += tree[idx];
		idx -= (idx & (-idx));
	}

	return ret;
}

void range_update(int s, int e, long long value)
{
	update(s, value, tree1);
	update(e + 1, -value, tree1);
	update(s, (1 - s) * value, tree2);
	update(e + 1, e * value, tree2);
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
	int x;
	long long ans;
	int cur;
	int c;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 2; i <= n; i++)
	{
		cin >> x;

		v[x].push_back(i);
	}

	dfs1(1);
	dfs2(1);

	while (q--)
	{
		cin >> x;

		nodes.resize(x);
		for (i = 0; i < x; i++)
		{
			cin >> nodes[i];
		}

		ans = 0;
		for (i = 0; i < x; i++)
		{
			cur = nodes[i];

			while (top[cur] != 0)
			{
				ans += get(in[cur], tree1) * in[cur] + get(in[cur], tree2);
				ans -= get(in[top[cur]] - 1, tree1) * (in[top[cur]] - 1) + get(in[top[cur]] - 1, tree2);
				cur = par[top[cur]];
			}

			ans += get(in[cur], tree1) * in[cur] + get(in[cur], tree2);

			ans -= i;

			cur = nodes[i];

			while (top[cur] != 0)
			{
				range_update(in[top[cur]], in[cur], 1);
				cur = par[top[cur]];
			}

			range_update(in[1], in[cur], 1);
		}

		cout << ans << '\n';

		for (i = 0; i < x; i++)
		{
			cur = nodes[i];

			while (top[cur] != 0)
			{
				range_update(in[top[cur]], in[cur], -1);
				cur = par[top[cur]];
			}

			range_update(in[1], in[cur], -1);
		}
	}
}
