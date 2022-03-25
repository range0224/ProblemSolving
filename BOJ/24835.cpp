#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int> v[100010];
int par[20][100010];
int depth[100010];

void dfs(int cur, int prv)
{
	int i;

	par[0][cur] = prv;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (v[cur][i] == prv) continue;

		depth[v[cur][i]] = depth[cur] + 1;
		dfs(v[cur][i], cur);
	}
}

int get_dist(int x, int y)
{
	int i;
	int d;

	if (depth[x] < depth[y]) swap(x, y);

	d = depth[x] - depth[y];
	for (i = 19; i >= 0; i--)
	{
		if (d & (1 << i)) x = par[i][x];
	}

	if (x == y) return d;

	for (i = 19; i >= 0; i--)
	{
		if (par[i][x] != par[i][y])
		{
			d += 2 * (1 << i);

			x = par[i][x];
			y = par[i][y];
		}
	}

	return d + 2;
}

int main()
{
	int q;
	int i, j;
	int a, b, c, d, e;
	int dist;
	int cycle;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1, -1);

	for (i = 1; i < 20; i++)
	{
		for (j = 1; j <= n; j++)
		{
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c >> d >> e;

		cycle = get_dist(a, b) + 1;

		dist = get_dist(c, d);
		if (dist <= e && (e - dist) % 2 == 0)
		{
			cout << "YES\n";
			continue;
		}

		dist = get_dist(c, a) + get_dist(a, d);
		if (dist <= e && ((e - dist) % 2 == 0 || (cycle % 2 == 1 && e - dist >= cycle)))
		{
			cout << "YES\n";
			continue;
		}

		dist = get_dist(c, b) + get_dist(b, d);
		if (dist <= e && ((e - dist) % 2 == 0 || (cycle % 2 == 1 && e - dist >= cycle)))
		{
			cout << "YES\n";
			continue;
		}

		dist = get_dist(c, a) + 1 + get_dist(b, d);
		if (dist <= e && ((e - dist) % 2 == 0 || (cycle % 2 == 1 && e - dist >= cycle)))
		{
			cout << "YES\n";
			continue;
		}

		dist = get_dist(c, b) + 1 + get_dist(a, d);
		if (dist <= e && ((e - dist) % 2 == 0 || (cycle % 2 == 1 && e - dist >= cycle)))
		{
			cout << "YES\n";
			continue;
		}

		cout << "NO\n";
	}
}
