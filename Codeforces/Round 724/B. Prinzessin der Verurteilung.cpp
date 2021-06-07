#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
 
int n;
string str;
map<string, int> m;
 
int main()
{
	int t;
	int i, j, k;
	string s;
	bool flag;
 
	cin >> t;
	while (t--)
	{
		cin >> n >> str;
 
		m.clear();
		for (i = 0; i < str.length(); i++)
		{
			s = "";
			for (j = 0; j < 3; j++)
			{
				if (i + j >= n) break;
 
				s += str[i + j];
 
				m[s] = 1;
			}
		}
 
		flag = false;
		for (i = 'a'; i <= 'z'; i++)
		{
			s = (char)i;
			if (m.find(s) == m.end())
			{
				cout << s << '\n';
				flag = true;
				break;
			}
		}
 
		if (flag) continue;
 
		for (i = 'a'; i <= 'z'; i++)
		{
			if (flag) break;
 
			for (j = 'a'; j <= 'z'; j++)
			{
				s = (char)i;
				s += (char)j;
 
				if (m.find(s) == m.end())
				{
					cout << s << '\n';
					flag = true;
					break;
				}
			}
		}
 
		if (flag) continue;
 
		for (i = 'a'; i <= 'z'; i++)
		{
			if (flag) break;
 
			for (j = 'a'; j <= 'z'; j++)
			{
				if (flag) break;
 
				for (k = 'a'; k <= 'z'; k++)
				{
					s = (char)i;
					s += (char)j;
					s += (char)k;
 
					if (m.find(s) == m.end())
					{
						cout << s << '\n';
						flag = true;
						break;
					}
				}
			}
		}
	}
}
