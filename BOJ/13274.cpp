#include<iostream>
#include<algorithm>
using namespace std;

int n;
long long arr[100010];
long long arr2[100010];

int main()
{
	int q;
	int i;
	int a, b, c;
	int idx;
	int x, y;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	sort(arr + 1, arr + (n + 1));
	
	while (q--)
	{
		cin >> a >> b >> c;

		for (i = a; i <= b; i++)
		{
			arr[i] += c;
		}

		x = 1;
		y = a;
		idx = 1;
		while (x <= n && y <= b && idx <= n)
		{
			if (x == a) x = b + 1;

			if (x <= n && arr[x] < arr[y]) arr2[idx++] = arr[x++];
			else arr2[idx++] = arr[y++];
		}

		while (x <= n)
		{
			if (x == a) x = b + 1;
			
			if(x <= n) arr2[idx++] = arr[x++];
		}
		while (y <= b)
		{
			arr2[idx++] = arr[y++];
		}

		for (i = 1; i <= n; i++) arr[i] = arr2[i];
	}

	for (i = 1; i <= n; i++)
	{
		cout << arr[i] << ' ';
	}
}
