#include<iostream>
#include<string>
#include<vector>
using namespace std;

string a, b;

void recur(int s1, int e1, int s2, int e2)
{
	int i;
	int idx;

	if (s1 > e1 || s2 > e2) return;

	for (i = s2; i <= e2; i++)
	{
		if (b[i] == a[s1])
		{
			idx = i;
			break;
		}
	}

	recur(s1 + 1, s1 + idx - s2, s2, idx - 1);
	recur(s1 + idx - s2 + 1, e1, idx + 1, e2);

	cout << b[idx];
}

int main()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	while (cin >> a)
	{
		cin >> b;

		recur(0, a.length() - 1, 0, b.length() - 1);
		cout << '\n';
	}
}
