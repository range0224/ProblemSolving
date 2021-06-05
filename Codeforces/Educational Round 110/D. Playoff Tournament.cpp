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
 
int SIZE;
int len;
int n;
string str;
int dp[1000010];
int toidx[1000010];
int tos[1000010];
 
int main()
{
	int q;
	int i;
	int a;
	char b;
	int idx;
 
	cin >> n;
	cin >> str;
 
	SIZE = (1 << (n + 1));
	len = (1 << n);
 
	for (i = 0; i < len; i++)
	{
		dp[i + len] = 1;
	}
 
	idx = 2 * len;
	for (i = 0; i < str.length(); i++)
	{
		if ((idx & (-idx)) == idx) idx /= 4;
 
		toidx[i] = idx;
		tos[idx] = i;
 
		if (str[i] == '0') dp[idx] = dp[2 * idx];
		else if (str[i] == '1') dp[idx] = dp[2 * idx + 1];
		else dp[idx] = dp[2 * idx] + dp[2 * idx + 1];
 
		idx++;
	}
 
	cin >> q;
	while (q--)
	{
		cin >> a >> b;
 
		a--;
 
		str[a] = b;
		idx = toidx[a];
 
		while (idx >= 1)
		{
			if (str[a] == '0') dp[idx] = dp[2 * idx];
			else if (str[a] == '1') dp[idx] = dp[2 * idx + 1];
			else dp[idx] = dp[2 * idx] + dp[2 * idx + 1];
 
			idx /= 2;
			a = tos[idx];
		}
 
		cout << dp[1] << '\n';
	}
}
