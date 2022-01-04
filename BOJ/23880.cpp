#include<iostream>
#include<cstring>
using namespace std;

int n, m;
char arr[60][60];
long long dp[60][60][5][2];

int main()
{
	int t;
	int i, j, k;
	long long ans;

	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}

		memset(dp, 0, sizeof(dp));

		if(arr[0][1] != 'H') dp[0][1][0][0] = 1;
		if(arr[1][0] != 'H') dp[1][0][0][1] = 1;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == 0 && j == 0) continue;

				for (k = 0; k <= m; k++)
				{
					if (j + 1 < n && arr[i][j + 1] != 'H')
					{
						dp[i][j + 1][k][0] += dp[i][j][k][0];
						dp[i][j + 1][k + 1][0] += dp[i][j][k][1];
					}
					if (i + 1 < n && arr[i + 1][j] != 'H')
					{
						dp[i + 1][j][k][1] += dp[i][j][k][1];
						dp[i + 1][j][k + 1][1] += dp[i][j][k][0];
					}
				}
			}
		}

		ans = 0;
		for (k = 0; k <= m; k++)
		{
			ans += dp[n - 1][n - 1][k][0] + dp[n - 1][n - 1][k][1];
		}
		cout << ans << '\n';
	}
}
