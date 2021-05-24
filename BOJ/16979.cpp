#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n, m;
vector<pair<int, int>> v, v2;
int arr[100010];
int tree[100010];
vector<pair<pair<int, int>, int>> query;
long long ans[100010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
	else return a.first.second < b.first.second;
}

void update(int idx, int v)
{
	while (idx <= n)
	{
		tree[idx] += v;
		idx += (idx & (-idx));
	}
}

int get(int idx)
{
	int ret = 0;

	while (idx)
	{
		ret += tree[idx];
		idx -= (idx & (-idx));
	}

	return ret;
}

int main()
{
	int i;
	int a, b;
	long long answer = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		v.push_back(make_pair(arr[i], i));
	}

	sort(v.begin(), v.end());

	v2.push_back(make_pair(1, v[0].second));
	for (i = 1; i < v.size(); i++)
	{
		if (v[i].first == v[i - 1].first) v2.push_back(make_pair(v2[i - 1].first, v[i].second));
		else v2.push_back(make_pair(v2[i - 1].first + 1, v[i].second));
	}

	for (i = 0; i < v2.size(); i++)
	{
		arr[v2[i].second] = v2[i].first;
	}

	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(make_pair(a, b), i));
	}

	sort(query.begin(), query.end(), comp);

	a = query[0].first.first;
	b = query[0].first.second;
	for (i = a; i <= b; i++)
	{
		answer += get(n) - get(arr[i]);
		update(arr[i], 1);
	}
	ans[query[0].second] = answer;

	for (i = 1; i < query.size(); i++)
	{
		while (a < query[i].first.first)
		{
			answer -= get(arr[a] - 1);
			update(arr[a], -1);
			a++;
		}
		while (a > query[i].first.first)
		{
			a--;
			answer += get(arr[a] - 1);
			update(arr[a], 1);
		}
		while (b < query[i].first.second)
		{
			b++;
			answer += get(n) - get(arr[b]);
			update(arr[b], 1);
		}
		while (b > query[i].first.second)
		{
			answer -= get(n) - get(arr[b]);
			update(arr[b], -1);
			b--;
		}

		ans[query[i].second] = answer;
	}

	for (i = 0; i < m; i++)
	{
		cout << ans[i] << '\n';
	}
}
