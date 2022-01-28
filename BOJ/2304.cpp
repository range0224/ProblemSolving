#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
int arr[1020];
int prefix[1020];
int suffix[1020];

int main()
{
	int i;
	int a, b;
	int ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		arr[a] = b;
	}

	for (i = 1; i < 1010; i++)
	{
		prefix[i] = max(prefix[i - 1], arr[i]);
	}

	for (i = 1010; i >= 1; i--)
	{
		suffix[i] = max(suffix[i + 1], arr[i]);
	}

	ans = 0;
	for (i = 1; i <= 1010; i++)
	{
		ans += min(prefix[i], suffix[i]);
	}

	cout << ans;
}
