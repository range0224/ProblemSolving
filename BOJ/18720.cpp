#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

long long n, d;
long long arr[400010];

int main()
{
	int t;
	int i;
	priority_queue<long long> pq;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> n >> d;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
		for (i = n; i <= 2 * n + 1; i++)
		{
			arr[i] = -(i - n + 1) * d;
		}

		sort(arr, arr + (2 * n + 1));

		while (!pq.empty()) pq.pop();

		ans = 0;
		for (i = 0; i < 2 * n + 1; i++)
		{
			arr[i] -= i * d;

			pq.push(arr[i]);

			if (pq.top() > arr[i])
			{
				if(i >= n + 1) ans += pq.top() - arr[i];
				pq.pop();
				pq.push(arr[i]);
			}
		}

		cout << ans << '\n';
	}
}
