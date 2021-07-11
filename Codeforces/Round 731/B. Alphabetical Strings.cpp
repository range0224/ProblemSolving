#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
using namespace std;
 
int pos[500];
 
int main()
{
	int t;
	int i;
	string str;
	int s, e;
	bool ans;
 
	cin >> t;
	while (t--)
	{
		cin >> str;
 
		for (i = 'a'; i <= 'z'; i++) pos[i] = -100;
 
		for (i = 0; i < str.length(); i++)
		{
			pos[str[i]] = i;
		}
 
		if (pos['a'] == -100)
		{
			cout << "NO\n";
			continue;
		}
 
		ans = true;
		s = pos['a'];
		e = s;
		for (i = 'b'; i < 'a' + str.length(); i++)
		{
			if (pos[i] == s - 1) s--;
			else if (pos[i] == e + 1) e++;
			else
			{
				ans = false;
				break;
			}
		}
 
		if (ans) cout << "YES\n";
		else cout << "NO\n";
	}
}
