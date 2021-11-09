#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;
vector<int> v1[300010], v2[300010];
int par[300010];
int sz[300010];
int sz1[300010], sz2[300010];
int num1[300010], num2[300010];
vector<pair<int, int>> v;

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

	par[a] = b;
	sz[b] += sz[a];
}

void dfs(int cur, vector<int> v[300010], int sz[300010], int num[300010])
{
	int i;

	if (cur <= k)
	{
		num[cur] = cur;
		sz[cur] = 1;
	}

	for (i = 0; i < v[cur].size(); i++)
	{
		dfs(v[cur][i], v, sz, num);

		sz[cur] += sz[v[cur][i]];
		num[cur] = num[v[cur][i]];
	}
}

int main()
{
	int i, j;
	int a;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	for (i = 1; i <= n; i++)
	{
		cin >> a;

		v1[a].push_back(i);
	}
	for (i = 1; i <= m; i++)
	{
		cin >> a;

		v2[a].push_back(i);
	}

	for (i = 1; i <= k; i++)
	{
		par[i] = i;
		sz[i] = 1;
	}

	dfs(v1[0][0], v1, sz1, num1);
	dfs(v2[0][0], v2, sz2, num2);

	for (i = k + 1; i <= n; i++)
	{
		if(v1[i].size() > 1) v.push_back(make_pair(sz1[i], i));
	}
	for (i = k + 1; i <= m; i++)
	{
		if(v2[i].size() > 1) v.push_back(make_pair(sz2[i], i + 300010));
	}

	sort(v.begin(), v.end());

	for (i = 0; i < v.size(); i++)
	{
		if (v[i].second < 300010)
		{
			a = v[i].second;

			for (j = 0; j < v1[a].size(); j++)
			{
				union_(num1[a], num1[v1[a][j]]);
			}

			if (sz[find(num1[a])] > v[i].first)
			{
				cout << "NO";
				return 0;
			}
		}
		else
		{
			a = v[i].second - 300010;

			for (j = 0; j < v2[a].size(); j++)
			{
				union_(num2[a], num2[v2[a][j]]);
			}

			if (sz[find(num2[a])] > v[i].first)
			{
				cout << "NO";
				return 0;
			}
		}
	}

	cout << "YES";
}
