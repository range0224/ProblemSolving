#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

const int MAXV = 100010;
int n, m, k;
int arr[MAXV];
vector<int> singer[MAXV];
vector<int> v[MAXV];
int in[MAXV], out[MAXV];
vector<pair<int, pair<int, int>>> query;
vector<pair<int, int>> tv;
int s[MAXV], e[MAXV];
int ans[MAXV];
long long tree[MAXV];
int cnt = 1;

void update(int idx, int value)
{
	while (idx <= n)
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

void dfs(int cur)
{
	int i;

	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		dfs(v[cur][i]);
	}
	out[cur] = cnt - 1;
}

int main()
{
	int i, j;
	int a, b, c;
	int idx;
	long long sum;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	for (i = 2; i <= n; i++)
	{
		cin >> a;

		v[a].push_back(i);
	}
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		singer[arr[i]].push_back(i);
	}
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		query.push_back(make_pair(a, make_pair(b, c)));
	}

	sort(query.begin(), query.end());

	for (i = 1; i <= n; i++)
	{
		s[i] = 0;
		e[i] = m - 1;
		ans[i] = m;
	}

	dfs(1);

	while (1)
	{
		tv.clear();

		for (i = 1; i <= n; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		memset(tree, 0, sizeof(tree));

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < m && idx <= tv[i].first)
			{
				a = query[idx].second.first;
				b = query[idx].second.second;
				update(in[a], b / (out[a] - in[a] + 1));
				update(out[a] + 1, -b / (out[a] - in[a] + 1));

				idx++;
			}

			a = tv[i].second;
			sum = 0;
			for (j = 0; j < singer[a].size(); j++)
			{
				sum += get(in[singer[a][j]]);
			}

			if (sum > k * singer[a].size())
			{
				ans[a] = tv[i].first;
				e[a] = tv[i].first - 1;
			}
			else s[a] = tv[i].first + 1;
		}
	}

	for (i = 1; i <= n; i++)
	{
		if (ans[arr[i]] == m) cout << -1 << '\n';
		else cout << query[ans[arr[i]]].first << '\n';
	}
}
