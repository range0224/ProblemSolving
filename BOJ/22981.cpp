#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long m;
long long arr[200010];

int main()
{
	int i;
	long long ans = 1LL << 60;
	long long x;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	for (i = 1; i < n; i++)
	{
		x = arr[0] * i + arr[i] * (n - i);
		ans = min(ans, m / x + (m % x != 0));
	}

	cout << ans;
}
