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
int status;
 
int main()
{
	int t;
	int i;
	int s;
	long long ans;
	int cnt;
 
	cin >> t;
	while (t--)
	{
		cin >> str;
 
		s = 0;
		ans = 1;
		cnt = (str[0] == '?');
		status = str[0];
		for (i = 1; i < str.length(); i++)
		{
			if (status == '0') status = '1';
			else if (status == '1') status = '0';
 
			if (status == '?')
			{
				ans += i - s + 1;
				if (str[i] != '?') status = str[i];
			}
			else if (status == '0')
			{
				if (str[i] == '1')
				{
					s = i - cnt;
					status = '1';
				}
				ans += i - s + 1;
			}
			else
			{
				if (str[i] == '0')
				{
					s = i - cnt;
					status = '0';
				}
				ans += i - s + 1;
			}
 
			if (str[i] == '?') cnt++;
			else cnt = 0;
		}
 
		cout << ans << '\n';
	}
}
