#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;

bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.second < b.second;
}

int main()
{
	int i;
	int a, b;
	stack<pair<int, int>> st;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a - b, a + b));
	}

	sort(v.begin(), v.end(), comp);

	for (i = 0; i < n - 1; i++)
	{
		if (v[i].second == v[i + 1].second)
		{
			cout << "NO";
			return 0;
		}
	}

	st.push(make_pair(-10000000, -100000000));
	for (i = 0; i < v.size(); i++)
	{
		while (st.top().first > v[i].first) st.pop();

		if (st.top().first <= v[i].first && st.top().second >= v[i].first)
		{
			cout << "NO";
			return 0;
		}

		st.push(v[i]);
	}

	cout << "YES";
}
