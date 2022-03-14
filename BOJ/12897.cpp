#include<iostream>
using namespace std;

const int MOD = 1000000007;
int n;

long long recur(long long x, long long y)
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
	int i;
	long long ans;
	long long mul;

	cin >> n;

	ans = 0;
	mul = 2;
	for (i = 1; i <= n; i++)
	{
		mul *= n - i + 1;
		mul %= MOD;
		mul *= recur(i, MOD - 2);
		mul %= MOD;

		ans += mul;
		ans %= MOD;

		mul *= 2;
		mul %= MOD;
	}

	cout << ans;
}
