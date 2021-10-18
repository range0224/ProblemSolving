#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[5010];

bool check(int x)
{
	int i;
	int cnt;
	int sum;
	int mn, mx;

	cnt = 1;
	mn = arr[0];
	mx = arr[0];
	for (i = 1; i < n; i++)
	{
		mn = min(mn, arr[i]);
		mx = max(mx, arr[i]);

		if (mx - mn > x)
		{
			cnt++;
			mn = arr[i];
			mx = arr[i];
		}
	}

	return cnt <= m;
}

int main()
{
	int i;
	int s, e, mid;
	int ans = 0;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	s = 0;
	e = 1000000000;
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
