#include<iostream>
#include<vector>
using namespace std;

int n;
int arr[100010];
vector<pair<int, int>> v[1000010];
int par[20][100010];
int dist[20][100010];
bool visited[100010];

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i].first]) continue;

		par[0][v[cur][i].first] = cur;
		dist[0][v[cur][i].first] = v[cur][i].second;

		dfs(v[cur][i].first);
	}
}

int main()
{
	int i, j;
	int a, b, c;
	int cur, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
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

	for (i = 1; i <= n; i++)
	{
		cur = i;
		d = arr[i];

		for (j = 19; j >= 0; j--)
		{
			if (dist[j][cur] <= d)
			{
				d -= dist[j][cur];
				cur = par[j][cur];
			}
		}

		if (cur <= 1) cout << 1 << '\n';
		else cout << cur << '\n';
	}
}
