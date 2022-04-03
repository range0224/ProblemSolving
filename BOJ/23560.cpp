#include<iostream>
using namespace std;

int recur(int s, int e, int v)
{
	int ret = 0;

	if (s == e) return 1;

	if (v % 3 == 1)
	{
		if (s % 3 == 1) ret += recur(s + 1, e, (v + 1) % 3);
		if (e % 3 == 1) ret += recur(s, e - 1, (v + 1) % 3);
	}
	else
	{
		if (s % 3 != 1) ret += recur(s + 1, e, (v + 1) % 3);
		if (e % 3 != 1) ret += recur(s, e - 1, (v + 1) % 3);
	}

	return ret;
}

int main()
{
	int n;

	cin >> n;

	cout << recur(0, 3 * n - 1, 0);
}
