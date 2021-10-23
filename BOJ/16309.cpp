#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[100010][2];

bool check(long long x)
{
	int i;
	long long sum;

	sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += max(0LL, x * arr[i][0] - arr[i][1]);

		if (sum >= m) return true;
	}

	return false;
}

int main()
{
	int i, j;
	long long s, e;
	long long mid;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 2; j++)
		{
			cin >> arr[i][j];
		}
	}

	s = 0;
	e = 1LL << 32;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (check(mid))
		{
			ans = mid;
			e = mid - 1;
		}
		else s = mid + 1;
	}

	cout << ans;
}
