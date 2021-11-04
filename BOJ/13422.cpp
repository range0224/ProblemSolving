#include<iostream>
using namespace std;

int n, m, k;
int arr[200010];

int main()
{
	int t;
	int i;
	int sum;
	int cnt;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> n >> m >> k;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
		for (i = n; i < 2 * n; i++)
		{
			arr[i] = arr[i - n];
		}

		sum = 0;
		for (i = 0; i < m; i++)
		{
			sum += arr[i];
		}

		cnt = 0;
		for (i = m; i < n + m; i++)
		{
			if (sum < k) cnt++;
			sum += arr[i] - arr[i - m];
		}

		if (n == m) cnt = (cnt != 0);

		cout << cnt << '\n';
	}
}
