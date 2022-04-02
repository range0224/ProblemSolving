#include<iostream>
using namespace std;

string s, p;

int main()
{
	int t, T;
	int i;
	int idx;

	cin >> T;
	for(t = 1; t <= T; t++)
	{
		cin >> s >> p;

		idx = 0;
		for (i = 0; i < p.length(); i++)
		{
			if (idx < s.length() && p[i] == s[idx]) idx++;
		}

		cout << "Case #" << t << ": ";
		if (idx == s.length()) cout << p.length() - s.length() << '\n';
		else cout << "IMPOSSIBLE\n";
	}
}
