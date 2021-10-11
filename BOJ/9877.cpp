#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, t;
int arr[510][510];
vector<pair<int, int>> v;
int to_num[510][510];
int par[250010];
int sz[250010];
int rnk[250010];
int s[250010];
int e[250010];
int ans[250010];
vector < pair<int, pair<int, int>>> edge;
int dx[2] = { 1,0 };
int dy[2] = { 0,1 };

bool in_range(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

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

	if (rnk[a] < rnk[b])
	{
		par[a] = b;
		sz[b] += sz[a];
	}
	else if (rnk[a] > rnk[b])
	{
		par[b] = a;
		sz[a] += sz[b];
	}
	else
	{
		par[a] = b;
		rnk[b]++;
		sz[b] += sz[a];
	}
}

void init()
{
	int i;

	for (i = 1; i <= n * m; i++)
	{
		par[i] = i;
		sz[i] = 1;
		rnk[i] = 0;
	}
}

int main()
{
	int i, j, k;
	int x;
	int nx, ny;
	vector<pair<int, int>> tv;
	int idx;
	long long answer;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> t;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cin >> x;

			if (x) v.push_back(make_pair(i, j));
		}
	}

	x = 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			to_num[i][j] = x++;
		}
	}

	for (i = 0; i < v.size(); i++)
	{
		s[i] = 0;
		e[i] = 1000000000;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			for (k = 0; k < 2; k++)
			{
				nx = i + dx[k];
				ny = j + dy[k];

				if (in_range(nx, ny)) edge.push_back(make_pair(abs(arr[i][j] - arr[nx][ny]), make_pair(to_num[i][j], to_num[nx][ny])));
			}
		}
	}

	sort(edge.begin(), edge.end());

	while (1)
	{
		tv.clear();

		for (i = 0; i < v.size(); i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		init();

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < edge.size() && edge[idx].first <= tv[i].first)
			{
				union_(edge[idx].second.first, edge[idx].second.second);
				idx++;
			}

			if (sz[find(to_num[v[tv[i].second].first][v[tv[i].second].second])] >= t)
			{
				ans[tv[i].second] = tv[i].first;
				e[tv[i].second] = tv[i].first - 1;
			}
			else
			{
				s[tv[i].second] = tv[i].first + 1;
			}
		}
	}

	answer = 0;
	for (i = 0; i < v.size(); i++)
	{
		answer += ans[i];
	}

	cout << answer;
}
