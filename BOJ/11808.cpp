#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
vector<pair<int, int>> v[1010];
long long dp[1010][110];

void dfs(int cur)
{
	int i, j, k;

	dp[cur][0] = 0;
	dp[cur][1] = 0;
	if (cur == 1) dp[cur][1] = -1;

	for (i = 0; i < v[cur].size(); i++)
	{
		dfs(v[cur][i].first);

		for (j = m; j >= 1; j--)
		{
			for (k = 1; k <= j; k++)
			{
				if (dp[cur][j - k] == -1 || dp[v[cur][i].first][k] == -1) continue;

				dp[cur][j] = max(dp[cur][j], dp[cur][j - k] + dp[v[cur][i].first][k] + 2LL * v[cur][i].second * min(m - k + 1, k));
			}
		}
	}
}

int main()
{
	int t, T;
	int a, b;
	int i;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> T;
	for (t = 1; t <= T; t++)
	{
		cin >> n >> m;

		for (i = 1; i <= n; i++) v[i].clear();

		for (i = 2; i <= n; i++)
		{
			cin >> a >> b;

			v[a].push_back(make_pair(i, b));
		}

		memset(dp, -1, sizeof(dp));

		dfs(1);

		cout << "Case " << t << ": " << dp[1][m] << '\n';
	}
}
