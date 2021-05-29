#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n, m;
int arr[100010];
int tree[200010];
vector<pair<pair<int, int>, int>> v;
long long ans[100010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
	else return a.first.second < b.first.second;
}

void update(int idx, int value)
{
	while (idx <= 200000)
	{
		tree[idx] += value;
		idx += (idx & (-idx));
	}
}

long long get(int idx)
{
	long long ret = 0;

	while (idx >= 1)
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
	int q;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		answer += get(arr[i] + m);
		if (arr[i] > m) answer -= get(arr[i] - m - 1);
		update(arr[i], 1);
	}
	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			answer += get(arr[a] + m);
			if (arr[a] > m) answer -= get(arr[a] - m - 1);
			update(arr[a], 1);
		}
		while (b < v[i].first.second)
		{
			b++;

			answer += get(arr[b] + m);
			if (arr[b] > m) answer -= get(arr[b] - m - 1);
			update(arr[b], 1);
		}
		while (a < v[i].first.first)
		{
			update(arr[a], -1);
			answer -= get(arr[a] + m);
			if (arr[a] > m) answer += get(arr[a] - m - 1);

			a++;
		}
		while (b > v[i].first.second)
		{
			update(arr[b], -1);
			answer -= get(arr[b] + m);
			if (arr[b] > m) answer += get(arr[b] - m - 1);

			b--;
		}

		ans[v[i].second] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
