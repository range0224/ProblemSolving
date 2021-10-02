#include<iostream>
using namespace std;

const int MOD = 998244353;
int n;
int arr[5010];
int dp[5010];

int main()
{
	int i, j;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (i = 0; i < n; i++)
	{
		dp[i] = 1;
		for (j = 0; j < i; j++)
		{
			if (arr[i] > arr[j]) dp[i] = (dp[i] + dp[j]) % MOD;
		}

		cout << dp[i] << ' ';
	}
}
