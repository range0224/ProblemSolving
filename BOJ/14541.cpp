#include<iostream>
using namespace std;

int main()
{
	int n;
	int i;
	int a, b;
	int x;
	int ans;

	while (1)
	{
		cin >> n;

		if (n == -1) break;

		x = 0;
		ans = 0;
		for (i = 0; i < n; i++)
		{
			cin >> a >> b;

			ans += a * (b - x);
			x = b;
		}

		cout << ans << " miles\n";
	}
}
