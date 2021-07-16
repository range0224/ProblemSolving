#include<iostream>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 12;
const int len = 1 << 11;
int n;
int arr[1510][1510];
long long dp[1510][1510];
long long tree[1510][SIZE];
int s[1510];
int e[1510];

void update(int s, int e, int value, long long tree[SIZE])
{
	while (s <= n)
	{
		tree[s] += value;
		s += (s & (-s));
	}
	e++;
	while (e <= n)
	{
		tree[e] -= value;
		e += (e & (-e));
	}
}

long long get(int idx, long long tree[SIZE])
{
	long long ret = 0;

	while (idx >= 1)
	{
		ret += tree[idx];
		idx -= (idx & (-idx));
	}

	return ret;
}

long long get(int x, int y)
{
	return get(y, tree[x]);
}

int main()
{
	int q;
	int i, j;
	long long ans;
	char a;
	int b, c;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
		}
	}
	
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + arr[i][j];
		}
	}

	ans = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			ans += dp[i][j];

			update(j, j, dp[i][j], tree[i]);
		}
	}

	cout << ans << '\n';

	q = n;
	while (q--)
	{
		cin.ignore();

		cin >> a >> b >> c;

		if (a == 'U') x = 1;
		else x = -1;

		for (i = b + 1; i <= n; i++)
		{
			s[i] = n + 1;
			e[i] = 0;
		}
		s[b] = c;
		e[b] = c;

		for (i = b, j = c;;) {
			if (j < n && max(get(i - 1, j + 1), get(i, j)) + x == max(get(i - 1, j + 1), get(i, j) + x)) j++;
			else i++;
			if (i > n) break;
			e[i] = j;
		}

		for (i = b, j = c;;) {
			if (i < n && max(get(i + 1, j - 1), get(i, j)) + x == max(get(i + 1, j - 1), get(i, j) + x)) i++;
			else j++;
			if (j > n || e[i] < j) break;
			s[i] = min(s[i], j);
		}

		for (i = b; i <= n; i++)
		{
			if (s[i] > e[i]) continue;

			update(s[i], e[i], x, tree[i]);

			ans += x * (e[i] - s[i] + 1);
		}

		cout << ans << '\n';
	}
}
