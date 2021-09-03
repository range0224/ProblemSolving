#include<iostream>
#include<string>
using namespace std;

string str;
string s;
string p;

int main()
{
	int i, j;

	cin >> s >> p;

	for (i = 0; i < s.length(); i++)
	{
		str += s[i];

		if (str.length() >= p.length())
		{
			for (j = 0; j < p.length(); j++)
			{
				if (str[str.length() - j - 1] != p[p.length() - j - 1]) break;
			}

			if (j == p.length())
			{
				for (j = 0; j < p.length(); j++) str.pop_back();
			}
		}
	}

	if (str.empty()) cout << "FRULA";
	else cout << str;
}
