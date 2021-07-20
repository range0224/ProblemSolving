#include<iostream>
#include<string>
using namespace std;

int n, m, k;
string arr[30];
string str;

int main()
{
	int i, j;
	int s, e;
	long long ans = 0;

	cin >> n >> m >> k;
	for (i = 0; i < k; i++)
	{
		cin >> arr[i];
	}

	cin >> str;

	s = m - 1;
	e = m - 1;
	for (i = str.length() - 1; i >= 0; i--)
	{
		while (s > 0 && arr[str[i] - 'A'][s - 1] == 'R') s--;
		while (i != str.length() - 1 && e >= s && arr[str[i] - 'A'][e] == 'R') e--;

		if (s > e) continue;

		ans += (e - s) + 1;
	}

	cout << ans;
}
