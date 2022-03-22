#include<iostream>
using namespace std;

long long a, b;

long long get_sum(long long x)
{
	long long sum = 0;
	long long add = 45;
	long long ten = 10;
	int i;

	while (ten <= x)
	{
		sum += add * (x / ten);
		add *= 10;
		ten *= 10;
	}

	ten = 1;
	while (ten <= x)
	{
		for (i = 1; i < (x / ten) % 10; i++)
		{
			sum += ten * i;
		}
		ten *= 10;
	}

	ten = 1;
	while (ten <= x)
	{
		sum += (x / ten) % 10 * (x % ten + 1);
		ten *= 10;
	}

	return sum;
}

int main()
{
	int t;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> a >> b;

		cout << get_sum(b) - get_sum(a - 1) << '\n';
	}
}
