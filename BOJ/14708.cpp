#include<iostream>
using namespace std;

long long n;

int main()
{
	long long i, j, k;
	long long a;
	long long ans;
	long long x, y, z;
	long long s, e;
	long long mid;

	cin >> n;

	for (i = 1; i <= 1000010; i++)
	{
		if (i * i * i > n) break;
	}

	a = i - 1;

	ans = 1LL << 60;
	for (i = a - 4000; i <= a + 4000; i++)
	{
		if (i <= 0) continue;

		for (j = i; j <= i + 4000; j++)
		{
			k = j;
			s = j;
			e = j + 3000;
			while (s <= e)
			{
				mid = (s + e) / 2;

				if (i * j * mid >= n)
				{
					k = mid;
					e = mid - 1;
				}
				else s = mid + 1;
			}

			if (i * j * k < n) continue;

			if (ans > i * j + j * k + k * i)
			{
				ans = i * j + j * k + k * i;
				x = i;
				y = j;
				z = k;
			}
		}
	}

	cout << x << ' ' << y << ' ' << z;
}
