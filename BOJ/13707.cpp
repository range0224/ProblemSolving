#include<iostream>
using namespace std;

const int MOD = 1000000000;
int n, m;
int dp[5010][5010];

int main()
{
	int i, j;
	long long sum;

	cin >> n >> m;

	for (j = 0; j <= n; j++) dp[1][j] = 1;

	for (i = 2; i <= m; i++)
	{
		sum = 0;
		for (j = 0; j <= n; j++)
		{
			sum += dp[i - 1][j];
			sum %= MOD;

			dp[i][j] = sum;
		}
	}

	cout << sum;
}13
