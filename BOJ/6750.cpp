#include<iostream>
using namespace std;

string s = "IOSHZXN";

int main()
{
	int i, j;

	string str;

	cin >> str;
	
	for (i = 0; i < str.length(); i++)
	{
		for (j = 0; j < s.length(); j++)
		{
			if (str[i] == s[j]) break;
		}

		if (j == s.length())
		{
			cout << "NO";
			return 0;
		}
	}

	cout << "YES";
}
