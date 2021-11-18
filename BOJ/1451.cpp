#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
char arr[60][60];
long long prefix[60][60];

int main()
{
	int i, j;
	long long ans = 0;

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> &arr[i][1];
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + arr[i][j] - '0';
		}
	}

	for (i = 1; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			ans = max(ans, prefix[i][m] * (prefix[j][m] - prefix[i][m]) * (prefix[n][m] - prefix[j][m]));
		}
	}

	for (i = 1; i < m; i++)
	{
		for (j = i + 1; j < m; j++)
		{
			ans = max(ans, prefix[n][i] * (prefix[n][j] - prefix[n][i]) * (prefix[n][m] - prefix[n][j]));
		}
	}

	for (i = 1; i < n; i++)
	{
		for (j = 1; j < m; j++)
		{
			ans = max(ans, prefix[i][m] * (prefix[n][j] - prefix[i][j]) * (prefix[n][m] - prefix[n][j] - prefix[i][m] + prefix[i][j]));
		}
	}

	for (i = n; i > 1; i--)
	{
		for (j = 1; j < m; j++)
		{
			ans = max(ans, (prefix[n][m] - prefix[i - 1][m]) * prefix[i - 1][j] * (prefix[i - 1][m] - prefix[i - 1][j]));
		}
	}

	for (j = 1; j < m; j++)
	{
		for (i = 1; i < n; i++)
		{
			ans = max(ans, prefix[n][j] * (prefix[i][m] - prefix[i][j]) * (prefix[n][m] - prefix[i][m] - prefix[n][j] + prefix[i][j]));
		}
	}

	for (j = m; j > 1; j--)
	{
		for (i = 1; i < n; i++)
		{
			ans = max(ans, (prefix[n][m] - prefix[n][j - 1]) * prefix[i][j - 1] * (prefix[n][j - 1] - prefix[i][j - 1]));
		}
	}

	cout << ans;
}
