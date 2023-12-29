#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[500010];
long long prefix[500010];
long long suffix[500010];

int main()
{
	int i;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	for (i = 2; i < n; i += 2)
	{
		prefix[i] = prefix[i - 2] + arr[i - 1] - arr[i - 2];
	}

	for (i = n - 3; i >= 0; i -= 2)
	{
		suffix[i] = suffix[i + 2] + arr[i + 2] - arr[i + 1];
	}

	ans = 1LL << 60;
	for (i = 0; i < n - 2; i += 2)
	{
		ans = min(ans, prefix[i] + suffix[i + 2] + arr[i + 2] - arr[i]);
	}

	cout << ans;
}
