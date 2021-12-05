#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;

bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.second > b.second;
}

int main()
{
	int i;
	int a, b;
	int t;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a, b));
	}

	sort(v.begin(), v.end(), comp);

	t = 1000000000;
	for (i = 0; i < v.size(); i++)
	{
		t = min(t, v[i].second) - v[i].first;
	}

	cout << t;
}
