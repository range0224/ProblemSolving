#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int n, m;
int arr[300][300];
vector<pair<pair<int, int>, int>> v;
multiset<int> ms[300];
int ans[100010];

int main()
{
	int q;
	int i, j;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> q;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
		}
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	sort(v.begin(), v.end());

	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			ms[1].insert(arr[i][j]);
		}
	}
	for (i = 2; i <= n - m + 1; i++)
	{
		ms[i] = ms[i - 1];
		for (j = 1; j <= m; j++)
		{
			ms[i].erase(ms[i].find(arr[i - 1][j]));
			ms[i].insert(arr[i + m - 1][j]);
		}
	}
	
	a = 1;
	b = 1;
	for (i = 0; i < q; i++)
	{
		if (a != v[i].first.first)
		{
			a = v[i].first.first;
			b = 1;
		}

		while (b < v[i].first.second)
		{
			for (j = a; j < a + m; j++)
			{
				ms[a].erase(ms[a].find(arr[j][b]));
				ms[a].insert(arr[j][b + m]);
			}
			b++;
		}

		ans[v[i].second] = *ms[a].rbegin() - *ms[a].begin();
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
