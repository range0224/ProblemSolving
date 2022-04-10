#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string a, b;
bool arr[20][20];

bool check(char x, char y)
{
	string s1, s2;
	int i;

	for (i = 0; i < a.length(); i++)
	{
		if (a[i] == x || a[i] == y) s1 += a[i];
	}
	for (i = 0; i < b.length(); i++)
	{
		if (b[i] == x || b[i] == y) s2 += b[i];
	}

	return s1.compare(s2) == 0;
}

int main()
{
	int q;
	char i, j;
	string s;
	bool flag;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);

	cin >> a >> b;

	for (i = 'a'; i <= 'r'; i++)
	{
		for (j = i; j <= 'r'; j++)
		{
			arr[i - 'a'][j - 'a'] = check(i, j);
		}
	}

	cin >> q;
	while (q--)
	{
		cin >> s;

		flag = true;
		for (i = 0; i < s.length(); i++)
		{
			for (j = i; j < s.length(); j++)
			{
				if (!arr[min(s[i], s[j]) - 'a'][max(s[i], s[j]) - 'a']) flag = false;
			}
		}

		if (flag) cout << 'Y';
		else cout << 'N';
	}
}
