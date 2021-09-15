#include<iostream>
using namespace std;

long long dp[60];

int main()
{
	int t;
	int n;
	int i;

	dp[1] = 1;
	for (i = 2; i < 60; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2] + 1;
	}

	cin >> t;
	while (t--)
	{
		cin >> n;

		for (i = 1; i <= 60; i++)
		{
			if (dp[i] > n) break;
		}

		cout << i - 1 << '\n';
	}
}
