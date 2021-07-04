#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<int> v[100010];
int par[20][100010];
int depth[100010];
bool visited[100010];

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;

		depth[v[cur][i]] = depth[cur] + 1;
		par[0][v[cur][i]] = cur;
		dfs(v[cur][i]);
	}
}

int get_lca(int a, int b)
{
	int i;
	int gap;

	if (depth[a] < depth[b]) swap(a, b);

	gap = depth[a] - depth[b];

	for (i = 19; i >= 0; i--)
	{
		if (gap & (1 << i)) a = par[i][a];
	}

	if (a == b) return a;

	for (i = 19; i >= 0; i--)
	{
		if (par[i][a] != par[i][b])
		{
			a = par[i][a];
			b = par[i][b];
		}
	}

	return par[0][a];
}

int get_anc(int x, int dist)
{
	int i;

	for (i = 19; i >= 0; i--)
	{
		if (dist & (1 << i)) x = par[i][x];
	}

	return x;
}

int get_ans(int r, int lca, int a, int b, int c)
{
	int da, db, dc;

	da = depth[a] - depth[lca];
	db = depth[b] - depth[lca];
	dc = depth[c] - depth[r] + depth[lca] - depth[r];

	if (depth[a] == depth[b] && depth[b] == depth[c]) return r;
	else if (da == db && db == dc) return lca;
	else if (dc > da || dc > db)
	{
		if (da != db) return -1;
		else if ((dc - da) % 2) return -1;
		else if ((dc - da) / 2 > depth[lca] - depth[r]) return get_anc(c, dc - (dc - da) / 2);
		else return get_anc(lca, (dc - da) / 2);
	}
	else if (da > db && da > dc)
	{
		if (dc != db) return -1;
		else if ((da - dc) % 2) return -1;
		else return get_anc(a, da - (da - dc) / 2);
	}
	else if (db > da && db > dc)
	{
		if (dc != da) return -1;
		else if ((db - dc) % 2) return -1;
		else return get_anc(b, db - (db - dc) / 2);
	}
	else return -1;
}

int main()
{
	int q;
	int i, j;
	int a, b, c;
	int x, y, z;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1);

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
		cin >> a >> b >> c;
		
		x = get_lca(a, b);
		y = get_lca(b, c);
		z = get_lca(a, c);

		if (depth[x] >= depth[y] && depth[x] >= depth[z]) cout << get_ans(y, x, a, b, c) << '\n';
		else if (depth[y] >= depth[x] && depth[y] >= depth[z]) cout << get_ans(x, y, b, c, a) << '\n';
		else cout << get_ans(x, z, a, c, b) << '\n';
	}
}
