#include<iostream>
#include<vector>
using namespace std;

int n;
int arr[5010];
vector<pair<int, pair<int, int>>> v;

void get_ans(int idx)
{
	int nxt;

	v.push_back(make_pair(idx, make_pair(1, n)));
	nxt = arr[idx];
	arr[idx] = 0;
	idx = nxt;
	while (arr[idx] != 0)
	{
		v.push_back(make_pair(idx, make_pair(1, n)));
		nxt = arr[idx];
		arr[idx] = idx;
		idx = nxt;
	}
	v.push_back(make_pair(idx, make_pair(1, n)));
}

int main()
{
	int i;

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	for (i = 1; i <= n; i++)
	{
		if (arr[i] != i) get_ans(i);
	}

	cout << v.size() << '\n';
	for (i = 0; i < v.size(); i++)
	{
		cout << v[i].first << ' ' << v[i].second.first << ' ' << v[i].second.second << '\n';
	}
}
