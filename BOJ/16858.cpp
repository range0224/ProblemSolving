#include<iostream>
#include<vector>
#include<set>
using namespace std;

int n;
int arr[200010];
vector<pair<int, int>> v[200010];
int d[200010];
int par[200010];
int dist[200010];
long long depth[200010];
set<pair<long long, int>> s[200010];
long long ans;

void get_depth(int cur, long long d)
{
	int i;

	depth[cur] = d;
	for (i = 0; i < v[cur].size(); i++)
	{
		get_depth(v[cur][i].first, d + v[cur][i].second);
	}
}

int dfs(int cur)
{
	int i;
	vector<int> vs;
	int idx;

	for (i = 0; i < v[cur].size(); i++)
	{
		vs.push_back(dfs(v[cur][i].first));
	}

	idx = cur;
	for (i = 0; i < vs.size(); i++)
	{
		if (s[idx].size() < s[vs[i]].size())
		{
			for (auto it = s[idx].begin(); it != s[idx].end(); it++)
			{
				s[vs[i]].insert(*it);
			}
			idx = vs[i];
		}
		else
		{
			for (auto it = s[vs[i]].begin(); it != s[vs[i]].end(); it++)
			{
				s[idx].insert(*it);
			}
		}
	}

	if (d[cur] == -1)
	{
		s[idx].insert(make_pair(depth[cur], arr[cur]));
	}
	else
	{
		while (1)
		{
			if (s[idx].empty()) break;
			else if (s[idx].begin()->first > depth[cur] + d[cur]) break;
			else if (!arr[cur]) break;

			auto it = s[idx].lower_bound(make_pair(depth[cur] + d[cur] + 1, -2100000000));

			it--;

			if (arr[cur] >= it->second)
			{
				ans += it->second;
				arr[cur] -= it->second;
				s[idx].erase(it);
			}
			else
			{
				s[idx].insert(make_pair(it->first, it->second - arr[cur]));
				s[idx].erase(it);
				ans += arr[cur];
				arr[cur] = 0;
			}
		}
	}

	return idx;
}

int main()
{
	int i;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 1; i <= n; i++)
	{
		cin >> d[i];
	}
	for (i = 2; i <= n; i++)
	{
		cin >> par[i];
	}
	for (i = 2; i <= n; i++)
	{
		cin >> dist[i];
	}

	for (i = 2; i <= n; i++)
	{
		v[par[i]].push_back(make_pair(i, dist[i]));
	}

	get_depth(1, 0);

	dfs(1);

	cout << ans;
}
