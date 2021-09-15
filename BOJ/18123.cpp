#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
vector<int> v[40];
vector<int> v2[40];
vector<long long> ans;
int sz[40];
bool visited[40];

void get_sz(int cur)
{
	int i;

	sz[cur] = 1;
	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;

		get_sz(v[cur][i]);

		sz[cur] += sz[v[cur][i]];
		v2[cur].push_back(v[cur][i]);
	}
}

int get_centroid(int cur)
{
	int i;

	for (i = 0; i < v2[cur].size(); i++)
	{
		if (sz[v2[cur][i]] > n / 2) return get_centroid(v2[cur][i]);
	}

	return cur;
}

int second_centroid(int cent)
{
	int i, j;
	int nxt;
	int sum;
	bool flag;

	if (n % 2 == 1) return -1;

	for (i = 0; i < v2[cent].size(); i++)
	{
		nxt = v2[cent][i];

		sum = n - 1;
		flag = true;
		for (j = 0; j < v2[nxt].size(); j++)
		{
			if (sz[v2[nxt][j]] > n / 2) flag = false;

			sum -= sz[v2[nxt][j]];
		}

		if (flag && sum <= n / 2) return nxt;
	}

	return -1;
}

pair<long long, int> hashing(int cur, int prv)
{
	pair<long long, int> ret = make_pair(1LL, 1);
	vector<pair<long long, int>> tv;
	int i;

	for (i = 0; i < v[cur].size(); i++)
	{
		if (v[cur][i] == prv) continue;

		tv.push_back(hashing(v[cur][i], cur));
	}

	sort(tv.begin(), tv.end());

	for (i = 0; i < tv.size(); i++)
	{
		ret.first <<= tv[i].second;
		ret.first += tv[i].first;
		ret.second += tv[i].second;
	}
	ret.first <<= 1;
	ret.second++;

	return ret;
}

int main()
{
	int t;
	int i;
	int a, b;
	int cent;
	int cent2;
	int cnt;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n - 1; i++)
		{
			cin >> a >> b;

			v[a].push_back(b);
			v[b].push_back(a);
		}

		memset(visited, false, sizeof(visited));
		get_sz(0);

		cent = get_centroid(0);

		cent2 = second_centroid(cent);

		if (cent2 == -1) ans.push_back(hashing(cent, -1).first);
		else ans.push_back(max(hashing(cent, -1).first, hashing(cent2, -1).first));

		for (i = 0; i < n; i++)
		{
			v[i].clear();
			v2[i].clear();
		}
	}

	sort(ans.begin(), ans.end());

	cnt = 1;
	for (i = 1; i < ans.size(); i++)
	{
		if (ans[i] != ans[i - 1]) cnt++;
	}

	cout << cnt;
}
