#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

int n, m;
vector<int> v[100010];
vector<int> tv[100010];
int sz[100010][25];
int dp[100010][25];
int par[100010];

void get_tree(int cur, int prv)
{
	int i;

	par[cur] = prv;
	for (i = 0; i < tv[cur].size(); i++)
	{
		if (tv[cur][i] == prv) continue;

		v[cur].push_back(tv[cur][i]);
		get_tree(tv[cur][i], cur);
	}
}

void get_sz(int cur)
{
	int i, j;

	sz[cur][0] = 1;
	for (i = 0; i < v[cur].size(); i++)
	{
		get_sz(v[cur][i]);

		for (j = 1; j <= 20; j++)
		{
			sz[cur][j] += sz[v[cur][i]][j - 1];
		}
	}
}

void dfs(int cur, int cnt)
{
	int i;

	if (cur == 1)
	{
		dp[cur][cnt] = dp[cur][cnt - 1] + sz[cur][cnt];
	}
	else
	{
		dp[cur][cnt] = dp[par[cur]][cnt - 1] + sz[cur][cnt - 1] + sz[cur][cnt];
	}

	for (i = 0; i < v[cur].size(); i++) dfs(v[cur][i], cnt);
}

int main()
{
	int i;
	int a, b;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		tv[a].push_back(b);
		tv[b].push_back(a);
	}

	get_tree(1, 0);
	get_sz(1);

	ans = 0;
	for (i = 1; i <= n; i++) dp[i][0] = 1;
	for (i = 1; i <= m; i++)
	{
		dfs(1, i);
	}

	for (i = 1; i <= n; i++)
	{
		ans = max(ans, dp[i][m]);
	}

	cout << ans;
}
