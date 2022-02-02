#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long arr[610];
long long ans;

void check(int x, int y)
{
	int s, e;

	s = 0;
	e = n - 1;
	while (s < e)
	{
		while (s == x || s == y) s++;
		while (e == x || e == y) e--;
		if (s >= e) break;

		ans = min(ans, abs(arr[x] + arr[y] - (arr[s] + arr[e])));

		if (arr[s] + arr[e] > arr[x] + arr[y]) e--;
		else s++;
	}
}

int main()
{
	int i, j;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	ans = 1LL << 60;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			check(i, j);
		}
	}

	cout << ans;
}
