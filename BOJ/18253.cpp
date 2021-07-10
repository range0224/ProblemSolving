#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

typedef pair<pair<pair<int, int>, pair<int, int>>, int> pii;
int n, m;
int arr[10][100010];
long long ans[100010];
long long dist[10][100010];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;

pii make_pii(int a, int b, int c, int d, int e)
{
	return make_pair(make_pair(make_pair(a, b), make_pair(c, d)), e);
}

bool in_range(int x, int y, int l, int r)
{
	return x >= 1 && x <= n && y >= l && y <= r;
}

void get_ans(int sx, int sy, int l, int r, vector<pii> &v)
{
	int i, j;
	int x, y;
	long long d;
	int nx, ny;
	long long nd;

	for (i = 1; i <= n; i++)
	{
		for (j = l; j <= r; j++)
		{
			dist[i][j] = 1LL << 60;
		}
	}

	dist[sx][sy] = 0;
	pq.push(make_pair(0, make_pair(sx, sy)));
	while (!pq.empty())
	{
		x = pq.top().second.first;
		y = pq.top().second.second;
		d = pq.top().first;
		pq.pop();

		if (dist[x][y] != d) continue;

		for (i = 0; i < 4; i++)
		{
			nx = x + dx[i];
			ny = y + dy[i];

			if (!in_range(nx, ny, l, r) || dist[nx][ny] <= d + arr[nx][ny]) continue;

			dist[nx][ny] = d + arr[nx][ny];
			pq.push(make_pair(d + arr[nx][ny], make_pair(nx, ny)));
		}
	}

	for (i = 0; i < v.size(); i++)
	{
		ans[v[i].second] = min(ans[v[i].second], dist[v[i].first.first.first][v[i].first.first.second] + dist[v[i].first.second.first][v[i].first.second.second] + arr[sx][sy]);
	}
}

void recur(int s, int e, vector<pii> &v)
{
	int mid;
	vector<pii> l, r;
	int i;

	if (s > e) return;

	mid = (s + e) / 2;

	for (i = 0; i < v.size(); i++)
	{
		if (mid > v[i].first.second.second) l.push_back(v[i]);
		else if(mid < v[i].first.first.second) r.push_back(v[i]);
	}

	for (i = 1; i <= n; i++)
	{
		get_ans(i, mid, s, e, v);
	}

	if (!l.empty()) recur(s, mid - 1, l);
	if (!r.empty()) recur(mid + 1, e, r);
}

int main()
{
	int q;
	int a, b, c, d;
	int i, j;
	vector<pii> query;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			cin >> arr[i][j];
		}
	}

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b >> c >> d;

		if (b > d)
		{
			swap(a, c);
			swap(b, d);
		}
		query.push_back(make_pii(a, b, c, d, i));
	}

	memset(ans, 110, sizeof(ans));

	recur(1, m, query);

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
