#include<iostream>
using namespace std;

int main()
{
	int n, m;
	int x;
	int i;
	int cnt = 0;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> x;

		while (x % 2 == 0)
		{
			cnt++;
			x /= 2;
		}
	}

	if (cnt >= m) cout << 1;
	else cout << 0;
}
