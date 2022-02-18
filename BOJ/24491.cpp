#include<iostream>
#include<algorithm>
using namespace std;

long long check(long long a, long long b)
{
	long long ret;
	long long ta, tb;
	int abit, bbit;

	if (a > b) return 1LL << 60;
	else if (a == b) return 0;

	ta = a;
	tb = b;

	for (abit = 62;; abit--)
	{
		if (a & (1LL << abit)) break;
	}
	for (bbit = 62;; bbit--)
	{
		if (b & (1LL << bbit)) break;
	}

	tb /= (1LL << (bbit - abit));

	if (ta > tb) return check(1LL << (abit + 1), b) + (1LL << (abit + 1)) - a;
	else if (ta == tb) return check(2 * a, b) + 1;
	else return check(tb, b) + tb - a;
}

int main()
{
	int t;
	long long a, b;
	int i;
	int x;
	long long ans;

	cin >> t;
	while (t--)
	{
		cin >> a >> b;

		ans = 1LL << 60;
		x = 0;
		for (i = 0; i < 60; i++)
		{
			ans = min(ans, check(a, b) + i + x);

			if (a % 2)
			{
				a++;
				x++;
			}
			a /= 2;
		}

		cout << ans << '\n';
	}
}
