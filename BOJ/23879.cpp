#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[100010];

int main()
{
	int i;
	int x;
	long long ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> x;

		arr[i] += x;
	}
	for (i = 0; i < n; i++)
	{
		cin >> x;

		arr[i] -= x;
	}

	x = 0;
	ans = 0;
	for (i = 0; i < n; i++)
	{
		if (arr[i] > 0) ans += max(0, arr[i] - x);

		x = max(0, arr[i]);
	}

	x = 0;
	for (i = 0; i < n; i++)
	{
		arr[i] = -arr[i];

		if (arr[i] > 0) ans += max(0, arr[i] - x);

		x = max(0, arr[i]);
	}

	cout << ans;
}
