#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
int arr[510][510];
vector<pair<pair<int, int>, pair<int, int>>> query;
vector<pair<int, pair<int, int>>> v;
vector<pair<int, int>> tv;
int num[510][510];
int par[250010];
int s[100010];
int e[100010];
int ans[100010];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

int find(int x)
{
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	par[a] = b;
}

int main()
{
	int q;
	int i, j;
	int a, b, c, d;
	int idx = 1;
	int nx, ny;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	memset(arr, 110, sizeof(arr));

	cin >> n >> m >> q;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			cin >> arr[i][j];

			v.push_back(make_pair(arr[i][j], make_pair(i, j)));
			num[i][j] = idx++;
		}
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b >> c >> d;

		query.push_back(make_pair(make_pair(a, b), make_pair(c, d)));
	}

	sort(v.begin(), v.end());

	for (i = 0; i < q; i++)
	{
		s[i] = arr[query[i].first.first][query[i].first.second];
		e[i] = 1000000;
	}

	while (1)
	{
		tv.clear();

		for (i = 0; i < q; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		for (i = 1; i <= n * m; i++) par[i] = i;

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < v.size() && v[idx].first <= tv[i].first)
			{
				for (j = 0; j < 4; j++)
				{
					nx = v[idx].second.first + dx[j];
					ny = v[idx].second.second + dy[j];

					if (arr[nx][ny] <= tv[i].first) union_(num[v[idx].second.first][v[idx].second.second], num[nx][ny]);
				}

				idx++;
			}

			if (find(num[query[tv[i].second].first.first][query[tv[i].second].first.second]) == find(num[query[tv[i].second].second.first][query[tv[i].second].second.second]))
			{
				ans[tv[i].second] = tv[i].first;
				e[tv[i].second] = tv[i].first - 1;
			}
			else s[tv[i].second] = tv[i].first + 1;
		}
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
