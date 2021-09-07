#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int n, m;
vector<pair<int, int>> v[1010];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int prv[1010];
int dist[1010];
vector<int> ans;

int main()
{
	int i;
	int a, b, c;
	int cur, d;
	int nxt, nd;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));
	}
	cin >> a >> b;

	memset(dist, 110, sizeof(dist));
	pq.push(make_pair(0, a));
	dist[a] = 0;
	while (!pq.empty())
	{
		cur = pq.top().second;
		d = pq.top().first;
		pq.pop();

		if (dist[cur] != d) continue;

		for (i = 0; i < v[cur].size(); i++)
		{
			nxt = v[cur][i].first;
			nd = d + v[cur][i].second;

			if (dist[nxt] > nd)
			{
				pq.push(make_pair(nd, nxt));
				dist[nxt] = nd;
				prv[nxt] = cur;
			}
		}
	}

	cur = b;
	while (cur != 0)
	{
		ans.push_back(cur);
		cur = prv[cur];
	}

	cout << dist[b] << '\n';
	cout << ans.size() << '\n';
	for (i = ans.size() - 1; i >= 0; i--)
	{
		cout << ans[i] << ' ';
	}
}
