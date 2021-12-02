#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main()
{
	string str;
	int i;
	int ans;
	int cnt;
	int a, b;

	cin >> str;

	ans = 1;
	cnt = 1;
	for (i = 1; i < str.length(); i++)
	{
		if (str[i] == str[i - 1]) cnt++;
		else cnt = 1;

		ans = max(ans, cnt);
	}

	a = 0;
	b = 0;
	for (i = 0; i < str.length(); i++)
	{
		if (str[i] == 'K')
		{
			if (b) b--;

			a++;
		}
		else
		{
			if (a) a--;

			b++;
		}

		ans = max(ans, a + b);
	}

	cout << ans;
}
