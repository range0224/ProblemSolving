#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const int INF = 1e9 + 7;
int n, m, k;
vector<pair<int, int>> v[100010];
vector<pair<int, int>> query;
vector<pair<int, int>> tv;
vector<pair<int, int>> node;
vector<int> party;
int dist[100010];
int s[100010];
int e[100010];
int ans[100010];
int par[100010];

bool comp(pair<int, int> a, pair<int, int> b)
{
	if (a.first != b.first) return a.first > b.first;
	else return a.second < b.second;
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

	par[a] = b;
}

int main()
{
	int q;
	int i;
	int a, b, c;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	int cur, d;
	int nxt, nd;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k >> q;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}
	for (i = 0; i < k; i++)
	{
		cin >> a;

		party.push_back(a);
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));
	}

	for (i = 1; i <= n; i++) dist[i] = INF;

	for (i = 0; i < k; i++)
	{
		dist[party[i]] = 0;
		pq.push(make_pair(0, party[i]));
	}

	while (!pq.empty())
	{
		d = pq.top().first;
		cur = pq.top().second;
		pq.pop();

		if (dist[cur] != d) continue;

		for (i = 0; i < v[cur].size(); i++)
		{
			nxt = v[cur][i].first;
			nd = d + v[cur][i].second;

			if (dist[nxt] > nd)
			{
				dist[nxt] = nd;
				pq.push(make_pair(nd, nxt));
			}
		}
	}

	for (i = 1; i <= n; i++)
	{
		node.push_back(make_pair(dist[i], i));
	}

	sort(node.begin(), node.end(), comp);

	for (i = 0; i < q; i++)
	{
		s[i] = 0;
		e[i] = INF;
	}

	while (1)
	{
		for (i = 1; i <= n; i++) par[i] = i;
		tv.clear();
		for (i = 0; i < q; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end(), comp);

		a = 0;
		b = 0;
		while (a < tv.size() && b < node.size())
		{
			if (tv[a].first <= node[b].first)
			{
				cur = node[b].second;

				for (i = 0; i < v[cur].size(); i++)
				{
					nxt = v[cur][i].first;

					if (dist[nxt] >= tv[a].first) union_(cur, nxt);
				}

				b++;
			}
			else
			{
				cur = tv[a].second;

				if (find(query[cur].first) == find(query[cur].second))
				{
					ans[cur] = tv[a].first;
					s[cur] = tv[a].first + 1;
				}
				else e[cur] = tv[a].first - 1;

				a++;
			}
		}

		while (a < tv.size())
		{
			cur = tv[a].second;

			if (find(query[cur].first) == find(query[cur].second))
			{
				ans[cur] = tv[a].first;
				s[cur] = tv[a].first + 1;
			}
			else e[cur] = tv[a].first - 1;

			a++;
		}
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
