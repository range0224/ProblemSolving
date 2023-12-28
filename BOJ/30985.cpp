#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int n, m, k;
int arr[100010];
vector<pair<int, int>> v[100010];
long long dist[2][100010];

void get_dist(int idx, int s)
{
	int cur, nxt;
	long long d, nd;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	int i;

	memset(dist[idx], 50, sizeof(dist[idx]));

	pq.push(make_pair(0, s));
	dist[idx][s] = 0;
	while (!pq.empty())
	{
		cur = pq.top().second;
		d = pq.top().first;
		pq.pop();

		if (dist[idx][cur] != d) continue;

		for(i = 0; i < v[cur].size(); i++)
		{
			nxt = v[cur][i].first;
			nd = v[cur][i].second + d;

			if (dist[idx][nxt] <= nd) continue;

			dist[idx][nxt] = nd;
			pq.push(make_pair(nd, nxt));
		}
	}
}

int main()
{
	int i;
	int a, b, c;
	long long ans;

	cin >> n >> m >> k;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));
		v[b].push_back(make_pair(a, c));
	}
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	get_dist(0, 1);
	get_dist(1, n);

	ans = 1LL << 60;
	for (i = 1; i <= n; i++)
	{
		if (arr[i] == -1) continue;

		ans = min(ans, 1LL * (k - 1) * arr[i] + dist[0][i] + dist[1][i]);
	}

	if (ans == (1LL << 60)) ans = -1;

	cout << ans;
}
