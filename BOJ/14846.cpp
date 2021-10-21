#include<iostream>
using namespace std;

int n;
int arr[310][310];
int dp[310][310][12];

int main()
{
	int q;
	int i, j, k;
	int a, b, c, d;
	int cnt;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> arr[i][j];

			for (k = 1; k <= 10; k++)
			{
				dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k] - dp[i - 1][j - 1][k];
			}
			dp[i][j][arr[i][j]]++;
		}
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c >> d;

		cnt = 0;
		for (k = 1; k <= 10; k++)
		{
			if (dp[c][d][k] - dp[a - 1][d][k] - dp[c][b - 1][k] + dp[a - 1][b - 1][k]) cnt++;
		}

		cout << cnt << '\n';
	}
}
