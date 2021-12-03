#include<iostream>
using namespace std;

int n;
int arr[100010];
int arr2[100010];

int check(int s, int e, int v, int arr[100010])
{
	int mid;
	int ret = 0;

	while (s <= e)
	{
		mid = (s + e) / 2;

		if (arr[mid] < v)
		{
			ret = mid;
			s = mid + 1;
		}
		else e = mid - 1;
	}

	return ret;
}

int main()
{
	int q;
	int i;
	int a, b, c;
	int s, e, mid;
	int ans;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 1; i <= n; i++)
	{
		cin >> arr2[i];
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c;

		s = 1;
		e = a;
		ans = -1;
		while (s <= e)
		{
			mid = (s + e) / 2;

			x = check(1, b, arr[mid], arr2);
			
			if (x + mid == c)
			{
				ans = mid;
				break;
			}
			else if (x + mid < c) s = mid + 1;
			else e = mid - 1;
		}

		if (ans != -1)
		{
			cout << 1 << ' ' << ans << '\n';
			continue;
		}

		s = 1;
		e = b;
		ans = -1;
		while (s <= e)
		{
			mid = (s + e) / 2;

			x = check(1, a, arr2[mid], arr);

			if (x + mid == c)
			{
				ans = mid;
				break;
			}
			else if (x + mid < c) s = mid + 1;
			else e = mid - 1;
		}

		cout << 2 << ' ' << ans << '\n';
	}
}
