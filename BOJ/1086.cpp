#include<iostream>
#include<cstring>
using namespace std;

int n, m;
string s[20];
int arr[20];
int mul[60];
long long dp[1 << 16][110];

long long recur(int visit, int mod)
{
	int i;
	long long ret = 0;

	if (visit == (1 << n) - 1)
	{
		return mod == 0;
	}

	if (dp[visit][mod] != -1) return dp[visit][mod];

	for (i = 0; i < n; i++)
	{
		if (visit & (1 << i)) continue;

		ret += recur(visit | (1 << i), (mod * mul[s[i].length()] + arr[i]) % m);
	}

	return dp[visit][mod] = ret;
}

long long get_gcd(long long a, long long b)
{
	long long temp;

	while (a % b)
	{
		temp = a % b;
		a = b;
		b = temp;
	}

	return b;
}

int main()
{
	int i, j;
	long long x, y;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> s[i];
	}
	cin >> m;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < s[i].length(); j++)
		{
			arr[i] *= 10;
			arr[i] += s[i][j] - '0';
			arr[i] %= m;
		}
	}

	mul[0] = 1;
	for(i = 1; i < 60; i++)
	{
		mul[i] = mul[i - 1] * 10;
		mul[i] %= m;
	}

	y = 1;
	for (i = 2; i <= n; i++) y *= i;

	memset(dp, -1, sizeof(dp));

	x = recur(0, 0);

	if (x == 0)
	{
		cout << "0/1";
		return 0;
	}

	cout << x / get_gcd(x, y) << '/' << y / get_gcd(x, y);
}
