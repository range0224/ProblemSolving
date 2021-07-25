#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
vector<pair<int, pair<int, int>>> v;
vector<pair<int, int>> query;
vector<int> tv[1000010];
int s[100010];
int e[100010];
int ans[100010];
int ans2[100010];
int par[100010];
int sz[100010];

int find(int x)
{
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a == b) return;

	sz[b] += sz[a];
	par[a] = b;
}

int main()
{
	int q;
	int i, j;
	int a, b, c;
	bool flag;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		v.push_back(make_pair(c, make_pair(a, b)));
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));
	}

	sort(v.begin(), v.end());

	for (i = 0; i < q; i++)
	{
		s[i] = 1;
		e[i] = 1000000;
		ans[i] = -1;
	}

	while (1)
	{
		for (i = 0; i <= 1000000; i++) tv[i].clear();

		flag = false;
		for (i = 0; i < q; i++)
		{
			if (s[i] <= e[i])
			{
				flag = true;

				tv[(s[i] + e[i]) / 2].push_back(i);
			}
		}

		if (!flag) break;

		for (i = 1; i <= n; i++)
		{
			par[i] = i;
			sz[i] = 1;
		}

		idx = 0;
		for (i = 0; i <= 1000000; i++)
		{
			while (idx < v.size() && v[idx].first <= i)
			{
				union_(v[idx].second.first, v[idx].second.second);
				idx++;
			}

			for (j = 0; j < tv[i].size(); j++)
			{
				if (find(query[tv[i][j]].first) == find(query[tv[i][j]].second))
				{
					ans[tv[i][j]] = i;
					ans2[tv[i][j]] = sz[find(query[tv[i][j]].first)];
					e[tv[i][j]] = i - 1;
				}
				else s[tv[i][j]] = i + 1;
			}
		}
	}

	for (i = 0; i < q; i++)
	{
		if (ans[i] == -1) cout << -1 << '\n';
		else cout << ans[i] << ' ' << ans2[i] << '\n';
	}
}
