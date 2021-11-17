#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

int n, m;
char arr[510][510];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
bool wall[510][510];
int dist[510][510];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

bool in_range(int x, int y)
{
	return x >= 0 && x < n&& y >= 0 && y < m;
}

int main()
{
	int i, j, k;
	int x, y, d;
	int nx, ny, nd;
	int sx, sy;
	int ex, ey;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (arr[i][j] == '#') continue;

			for (k = 0; k < 4; k++)
			{
				nx = i + dx[k];
				ny = j + dy[k];

				if (in_range(nx, ny) && arr[nx][ny] == '#') wall[i][j] = true;
			}
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (arr[i][j] == 'S')
			{
				sx = i;
				sy = j;
				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'E')
			{
				ex = i;
				ey = j;
				arr[i][j] = '.';
			}
		}
	}

	memset(dist, 110, sizeof(dist));

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

			if (!in_range(nx, ny) || arr[nx][ny] == '#') continue;

			if (wall[x][y] && wall[nx][ny]) nd = d;
			else nd = d + 1;

			if (dist[nx][ny] > nd)
			{
				dist[nx][ny] = nd;
				pq.push(make_pair(nd, make_pair(nx, ny)));
			}
		}
	}

	cout << dist[ex][ey];
}
