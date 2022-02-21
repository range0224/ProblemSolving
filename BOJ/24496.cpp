#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long arr[100010];

int main()
{
	int t;
	int i;
	long long ans;
	long long x;

	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}

		ans = 0;
		x = arr[0];
		for (i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				if (i % 2 == 0)
				{
					ans = -1;
					break;
				}

				ans += (i + 1) * (x - arr[i + 1]);
				x = arr[i + 1];
			}
			else if(arr[i] < arr[i + 1])
			{
				if (i == n - 2 || arr[i + 2] < arr[i + 1] - x)
				{
					ans = -1;
					break;
				}

				ans += 2 * (arr[i + 1] - x);

				arr[i + 2] -= arr[i + 1] - x;
				arr[i + 1] = x;
			}
		}

		if (arr[n - 1] != x) ans = -1;

		cout << ans << '\n';
	}
}
