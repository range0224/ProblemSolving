#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v[100010];
bool visited[100010];
int depth[100010];
int par[20][100010];
long long dist[20][100010];

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i].first]) continue;

		depth[v[cur][i].first] = depth[cur] + 1;
		par[0][v[cur][i].first] = cur;
		dist[0][v[cur][i].first] = v[cur][i].second;
		dfs(v[cur][i].first);
	}
}

int get_lca(int a, int b)
{
	int i;
	int d;

	if (depth[a] < depth[b]) swap(a, b);

	d = depth[a] - depth[b];
	for (i = 19; i >= 0; i--)
	{
		if (d & (1 << i)) a = par[i][a];
	}

	for (i = 19; i >= 0; i--)
	{
		if (par[i][a] != par[i][b])
		{
			a = par[i][a];
			b = par[i][b];
		}
	}

	if (a == b) return a;
	else return par[0][a];
}

int main()
{
	int q;
	int a, b, c;
	int i, j;
	int d;
	int lca;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}

	dfs(1);

	for (i = 1; i < 20; i++)
	{
		for (j = 1; j <= n; j++)
		{
			par[i][j] = par[i - 1][par[i - 1][j]];
			dist[i][j] = dist[i - 1][par[i - 1][j]] + dist[i - 1][j];
		}
	}

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			ans = 0;

			if (depth[b] < depth[c]) swap(b, c);
			d = max(0, depth[b] - depth[c]);
			for (i = 19; i >= 0; i--)
			{
				if (d & (1 << i))
				{
					ans += dist[i][b];
					b = par[i][b];
				}
			}

			for (i = 19; i >= 0; i--)
			{
				if (par[i][b] != par[i][c])
				{
					ans += dist[i][b] + dist[i][c];
					b = par[i][b];
					c = par[i][c];
				}
			}

			if (b != c) ans += dist[0][b] + dist[0][c];

			cout << ans << '\n';
		}
		else
		{
			cin >> a >> b >> c;

			c--;

			lca = get_lca(a, b);

			if (depth[a] - depth[lca] >= c)
			{
				for (i = 19; i >= 0; i--)
				{
					if (c & (1 << i)) a = par[i][a];
				}

				cout << a << '\n';
			}
			else
			{
				c -= (depth[a] - depth[lca]);
				c = depth[b] - depth[lca] - c;

				for (i = 19; i >= 0; i--)
				{
					if (c & (1 << i)) b = par[i][b];
				}

				cout << b << '\n';
			}
		}
	}
}
