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
int arr[310];
vector<int> v;
 
int gcd(int a, int b)
{
	int temp;
 
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
	int x;
	bool flag;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		flag = false;
		for (i = 0; i < n; i++)
		{
			if (arr[i] < 0) flag = true;
		}
 
		if (flag)
		{
			cout << "NO\n";
			continue;
		}
 
		sort(arr, arr + n);
 
		x = arr[0];
		for (i = 1; i < n; i++)
		{
			x = gcd(x, arr[i] - arr[i - 1]);
		}
 
		v.clear();
		v.push_back(min(arr[0], x));
		for (i = 0; i < n; i++)
		{
			if (v[v.size() - 1] == arr[i]) continue;
 
			while (v.size() <= 300 && v[v.size() - 1] + x != arr[i]) v.push_back(v[v.size() - 1] + x);
			v.push_back(arr[i]);
		}
 
		if (v.size() <= 300 && v[v.size() - 1] == arr[n - 1])
		{
			cout << "YES\n";
			cout << v.size() << '\n';
			for (i = 0; i < v.size(); i++)
			{
				cout << v[i] << ' ';
			}
			cout << '\n';
		}
		else cout << "NO\n";
	}
}
