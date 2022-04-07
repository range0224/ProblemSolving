#include<iostream>
using namespace std;

int main()
{
	int n;
	int i;

	cin >> n;

	if (n % 4 == 0)
	{
		for (i = n / 2; i >= 1; i--) cout << i << '\n';
		for (i = n; i > n / 2; i--) cout << i << '\n';
	}
	else if (n % 4 == 2)
	{
		cout << n / 2 << '\n';
		for (i = 1; i < n / 2; i++) cout << i << '\n';
		for (i = n / 2 + 2; i <= n; i++) cout << i << '\n';
		cout << n / 2 + 1;
	}
	else
	{
		if (n == 3) cout << -1;
		else
		{
			cout << 2 << '\n';
			cout << 1 << '\n';
			cout << n << '\n';
			for (i = 3; i < n; i++) cout << i << '\n';
		}
	}
}
