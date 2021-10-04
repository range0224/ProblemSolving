#include<iostream>
#include<string>
using namespace std;

string str;
int cnt[30];
int cnt2[30];

bool check(bool same_length)
{
	int i;
	int a, b;

	a = 0;
	b = 0;
	for (i = 0; i < 26; i++)
	{
		if (cnt[i] == cnt2[i] - 1) a++;
		else if (cnt[i] == cnt2[i] + 1) b++;
		else if (cnt[i] != cnt2[i]) return false;
	}

	return (a == 1 && b == 1) || (a == 0 && b == 0 && !same_length);
}

int main()
{
	int q;
	string s;
	int i;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> str;

	for (i = 0; i < str.length(); i++) cnt[str[i] - 'a']++;

	cin >> q;
	while (q--)
	{
		cin >> s;

		if (s.length() < str.length())
		{
			cout << "NO\n";
			continue;
		}

		for (i = 0; i < 26; i++) cnt2[i] = 0;

		for (i = 0; i < str.length(); i++) cnt2[s[i] - 'a']++;

		if (check(s.length() == str.length()))
		{
			cout << "YES\n";
			continue;
		}
		for (i = str.length(); i < s.length(); i++)
		{
			cnt2[s[i - str.length()] - 'a']--;
			cnt2[s[i] - 'a']++;

			if (check(s.length() == str.length()))
			{
				cout << "YES\n";
				break;
			}
		}

		if (i == s.length())
		{
			cout << "NO\n";
		}
	}
}
