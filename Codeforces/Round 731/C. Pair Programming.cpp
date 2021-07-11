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
 
int line;
int n, m;
int arr[110];
int arr2[110];
vector<int> v;
 
int main()
{
	int t;
	int i;
	int a, b;
 
	cin >> t;
	while (t--)
	{
		cin >> line >> n >> m;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
		for (i = 0; i < m; i++)
		{
			cin >> arr2[i];
		}
 
		a = 0;
		b = 0;
		v.clear();
		while (a < n && b < m)
		{
			if (arr[a] > line && arr2[b] > line) break;
			else if (arr[a] > line)
			{
				if (!arr2[b]) line++;
				v.push_back(arr2[b++]);
			}
			else
			{
				if (!arr[a]) line++;
				v.push_back(arr[a++]);
			}
		}
		while (a < n)
		{
			if (arr[a] > line) break;
			else
			{
				if (!arr[a]) line++;
				v.push_back(arr[a++]);
			}
		}
		while (b < m)
		{
			if (arr2[b] > line) break;
			else
			{
				if (!arr2[b]) line++;
				v.push_back(arr2[b++]);
			}
		}
 
		if (v.size() < n + m) cout << -1 << '\n';
		else
		{
			for (i = 0; i < v.size(); i++)
			{
				cout << v[i] << ' ';
			}
			cout << '\n';
		}
	}
}
