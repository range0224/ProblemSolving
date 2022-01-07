#include<iostream>
using namespace std;

int n;
int arr[100010];
int cnt[50];

int main()
{
	int i, j;
	long long ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	ans = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= 30; j++)
		{
			if (arr[i] & (1 << j))
			{
				cnt[j] = i - cnt[j];
				cnt[j]++;
			}

			ans += cnt[j] * (1LL << j);
		}
	}

	cout << ans;
}
