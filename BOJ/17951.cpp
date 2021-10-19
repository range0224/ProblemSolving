#include<iostream>
using namespace std;

int n, m;
int arr[100010];

bool check(int x)
{
	int i;
	int cnt;
	int sum;

	cnt = 1;
	sum = arr[0];
	for (i = 1; i < n; i++)
	{
		if (sum >= x)
		{
			sum = 0;
			cnt++;
		}

		sum += arr[i];
	}

	return cnt > m || (cnt == m && sum >= x);
}

int main()
{
	int i;
	int s, e, mid;
	int ans;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	s = 0;
	e = 10000000;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (check(mid))
		{
			ans = mid;
			s = mid + 1;
		}
		else e = mid - 1;
	}

	cout << ans;
}
