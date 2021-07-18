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
 
string str;
 
int main()
{
	int t;
	int i;
	int ans;
 
	cin >> t;
	while (t--)
	{
		cin >> str;
 
		ans = 1;
		for (i = 0; i < str.length(); i++)
		{
			ans = max(ans, str[i] - '0');
		}
 
		cout << ans << '\n';
	}
}
