#include<iostream>
using namespace std;

const int MOD = 998244353;
int n, m, k;

int main()
{
	int i;
	int sum;
	long long ans;

	cin >> n >> m >> k;

	sum = 0;
	for (i = 1; i <= k; i++)
	{
		sum += i;
		sum %= MOD;
	}

	ans = 1LL * sum * sum;
	ans %= MOD;
	for (i = 0; i < n + m - 2; i++)
	{
		ans *= k;
		ans %= MOD;
	}
	ans *= m;
	ans %= MOD;

	for (i = 0; i < n - m + 1; i++) cout << ans << ' ';
}
