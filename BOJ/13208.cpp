#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

int n, m;
int arr[510];
int weight[510][510];
vector<int> v[510];
vector<pair<int, pair<pair<int, int>, pair<int, int>>>> edge;
vector<pair<int, pair<pair<int, int>, pair<int, int>>>> real_edge;
vector<pair<int, int>> query;
vector<pair<int, int>> pbs;
vector<int> values;
map<int, int> mp;
int rvmp[300000];
int num[510][510];
int par[300000];
int sz[300000];
long long s[300000];
long long e[300000];
int ans[300000];

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

	if (sz[a] > sz[b]) swap(a, b);
	if (sz[a] == sz[b]) sz[b]++;
	par[a] = b;
}

int main()
{
	int q;
	int i, j, k;
	int a, b, c, d;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		v[a].push_back(b);
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			weight[i][j] = arr[i] * arr[j];

			values.push_back(weight[i][j]);
		}
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < v[i].size(); j++)
		{
			for (k = 1; k <= n; k++)
			{
				edge.push_back(make_pair(max(weight[i][k], weight[v[i][j]][k]), make_pair(make_pair(i, k), make_pair(v[i][j], k))));
				edge.push_back(make_pair(max(weight[k][i], weight[k][v[i][j]]), make_pair(make_pair(k, i), make_pair(k, v[i][j]))));
			}
		}
	}

	sort(values.begin(), values.end());

	mp[values[0]] = 1;
	rvmp[1] = values[0];
	idx = 2;
	for (i = 1; i < values.size(); i++)
	{
		if (values[i] != values[i - 1])
		{
			rvmp[idx] = values[i];
			mp[values[i]] = idx++;
		}
	}

	for (i = 0; i < edge.size(); i++) edge[i].first = mp[edge[i].first];

	for (i = 0; i < q; i++)
	{
		s[i] = 0;
		e[i] = idx - 1;
	}

	idx = 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			num[i][j] = idx++;
		}
	}

	sort(edge.begin(), edge.end());

	for (i = 1; i <= n * n; i++)
	{
		par[i] = i;
		sz[i] = 1;
	}

	idx = 0;
	while (idx < edge.size())
	{
		a = edge[idx].second.first.first;
		b = edge[idx].second.first.second;
		c = edge[idx].second.second.first;
		d = edge[idx].second.second.second;

		if (find(num[a][b]) != find(num[c][d]))
		{
			union_(num[a][b], num[c][d]);
			real_edge.push_back(edge[idx]);
		}

		idx++;
	}

	while (1)
	{
		pbs.clear();

		for (i = 0; i < q; i++)
		{
			if (s[i] > e[i]) continue;

			pbs.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (pbs.empty()) break;

		sort(pbs.begin(), pbs.end());

		for (i = 1; i <= n * n; i++)
		{
			par[i] = i;
			sz[i] = 1;
		}

		idx = 0;
		for (i = 0; i < pbs.size(); i++)
		{
			while (idx < real_edge.size() && real_edge[idx].first <= pbs[i].first)
			{
				a = real_edge[idx].second.first.first;
				b = real_edge[idx].second.first.second;
				c = real_edge[idx].second.second.first;
				d = real_edge[idx].second.second.second;

				union_(num[a][b], num[c][d]);

				idx++;
			}

			a = query[pbs[i].second].first;
			b = query[pbs[i].second].second;

			if (find(num[a][b]) == find(num[b][a]))
			{
				ans[pbs[i].second] = pbs[i].first;
				e[pbs[i].second] = pbs[i].first - 1;
			}
			else s[pbs[i].second] = pbs[i].first + 1;
		}
	}

	for (i = 0; i < q; i++)
	{
		cout << rvmp[ans[i]] << '\n';
	}
}
