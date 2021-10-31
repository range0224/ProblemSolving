#include<iostream>
using namespace std;

int main()
{
	long long a, b;
	long long i;
	long long ans;
	long long x;

	cin >> a >> b;

	ans = b - a + 1;
	for (i = 2; i <= b; i *= 2)
	{
		x = b / i - (a - 1) / i;

		ans += i * x / 2;
	}

	cout << ans;
}
