#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int> v;

int main()
{
	long long s, e;
	int i;

	cin >> n;

	s = 1;
	e = 1;
	while (e <= 100000)
	{
		if (e * e - s * s == n)
		{
			v.push_back(e);
			s++;
			e++;
		}
		else if (e * e - s * s < n) e++;
		else s++;
	}

	if (v.empty()) cout << -1;
	else
	{
		for (i = 0; i < v.size(); i++)
		{
			cout << v[i] << '\n';
		}
	}
}
