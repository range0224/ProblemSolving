#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;
vector<int> arr[100010];
vector<pair<int, int>> v;
vector<pair<int, int>> tv;
int par[100010];
int rnk[100010];
int s[100010];
int e[100010];
int ans[100010];

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

	if (rnk[a] < rnk[b]) par[a] = b;
	else if (rnk[a] > rnk[b]) par[b] = a;
	else
	{
		par[a] = b;
		rnk[b]++;
	}
}

int main()
{
	int i, j;
	int a, b;
	int idx;
	bool flag;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	for (i = 1; i <= n; i++)
	{
		cin >> a;

		arr[a].push_back(i);
	}
	for (i = 0; i < k; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a, b));
	}

	for (i = 1; i <= m; i++)
	{
		s[i] = 0;
		e[i] = k;
		ans[i] = -1;
	}

	while (1)
	{
		tv.clear();

		for (i = 1; i <= m; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		for (i = 1; i <= n; i++)
		{
			par[i] = i;
			rnk[i] = 0;
		}

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < tv[i].first)
			{
				union_(v[idx].first, v[idx].second);
				idx++;
			}

			flag = true;
			for (j = 1; j < arr[tv[i].second].size(); j++)
			{
				if (find(arr[tv[i].second][j]) != find(arr[tv[i].second][j - 1]))
				{
					flag = false;
					break;
				}
			}

			if (flag)
			{
				ans[tv[i].second] = tv[i].first;
				e[tv[i].second] = tv[i].first - 1;
			}
			else s[tv[i].second] = tv[i].first + 1;
		}
	}

	for (i = 1; i <= m; i++)
	{
		cout << ans[i] << '\n';
	}
}
