#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[100010];
int prefix[100010];

int main()
{
	int i;
	int ans = -(1 << 30);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		prefix[i] = prefix[i - 1] + arr[i];
	}

	for (i = m; i <= n; i++)
	{
		ans = max(ans, prefix[i] - prefix[i - m]);
	}

	cout << ans;
}
