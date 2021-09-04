#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long m;
long long arr[100010];
bool used[100010];

int main()
{
	int i;
	int s, e;
	int cnt;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	cnt = 0;
	s = 0;
	e = n - 1;
	while (e >= 0 && arr[e] == m)
	{
		cnt++;
		used[e--] = true;
	}
	while (s < e)
	{
		if (2 * (arr[s] + arr[e]) >= m)
		{
			cnt++;
			used[s++] = true;
			used[e--] = true;
		}
		else
		{
			s++;
		}
	}

	s = 0;
	for (i = 0; i < n; i++)
	{
		s += !used[i];
	}

	cout << cnt + s / 3;
}
