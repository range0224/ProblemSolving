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
map<pair<int, int>, int> m;
 
int gcd(int a, int b)
{
	int temp;
 
	if (a == 0) return b;
	else if (b == 0) return a;
 
	while (a % b)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
 
	return b;
}
 
int main()
{
	int t;
	int i;
	int a, b;
	int x, y;
	int g;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		cin >> str;
 
		m.clear();
 
		a = 0;
		b = 0;
		for (i = 0; i < n; i++)
		{
			if (str[i] == 'D') a++;
			else b++;
 
			g = gcd(a, b);
			x = a / g;
			y = b / g;
 
			if (m.find(make_pair(x, y)) != m.end())
			{
				cout << m[make_pair(x, y)] + 1 << ' ';
				m[make_pair(x, y)]++;
			}
			else
			{
				cout << 1 << ' ';
				m[make_pair(x, y)] = 1;
			}
		}
		cout << '\n';
	}
}
