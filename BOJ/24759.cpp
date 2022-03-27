#include<iostream>
using namespace std;

int n, m;
int arr[100010];
int cnt[100010];

int main()
{
	int i;
	int sum;
	int s, e;

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	s = 1;
	e = 1;
	sum = arr[1] + arr[2];
	while (s <= n)
	{
		cnt[s]++;
		cnt[e + 1]--;
		if (e + 1 > n)
		{
			sum -= arr[s];
			s++;
		}
		else if (sum > m)
		{
			sum -= arr[s];
			s++;
		}
		else
		{
			e++;
			sum += arr[e + 1];
		}
	}

	sum = 0;
	for (i = 1; i <= n; i++)
	{
		sum += cnt[i];

		cout << sum << '\n';
	}
}
