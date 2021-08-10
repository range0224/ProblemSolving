#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int MOD = 1e9 + 7;
int n, m;
long long ncm[200010];
long long two[200010];
long long dp[200010];

long long recur(int x, int y)
{
	long long ret;

	if (y == 0) return 1;

	ret = recur(x, y / 2);

	ret *= ret;
	ret %= MOD;

	if (y % 2 == 0) return ret;
	else return (x * ret) % MOD;
}

int main()
{
	int t;
	int i;
	long long ans;
	long long mul;

	two[0] = 1;
	for (i = 1; i <= 200000; i++)
	{
		two[i] = two[i - 1] * 2;
		two[i] %= MOD;
	}

	cin >> t;
	while (t--)
	{
		cin >> n >> m;

		ncm[0] = 1;
		for (i = 1; i <= n; i++)
		{
			ncm[i] = ncm[i - 1];
			ncm[i] *= n - i + 1;
			ncm[i] %= MOD;
			ncm[i] *= recur(i, MOD - 2);
			ncm[i] %= MOD;
		}

		mul = 0;
		for (i = 0; i <= n; i += 2)
		{
			mul += ncm[i];
			mul %= MOD;
		}

		mul += n % 2;
		mul -= !(n % 2);

		ans = 1;
		for (i = 0; i < m; i++)
		{
			dp[i] = ans;

			ans *= mul;
			ans %= MOD;
		}

		if (n % 2 == 0)
		{
			for (i = 0; i < m; i++)
			{
				ans += (dp[i] * recur(two[m - i - 1], n)) % MOD;
				ans %= MOD;
			}
		}

		cout << ans << '\n';
	}
}
