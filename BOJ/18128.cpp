#include<iostream>
#include<queue>
using namespace std;

int n, m;
char arr[1010][1010];
int num[1010][1010];
int dist[1010][1010];
bool visited[1010][1010];
int par[1000010];
int rnk[1000010];
int dx[8] = { 1, 0, -1, 0, -1, -1, 1, 1 };
int dy[8] = { 0, 1, 0, -1, -1, 1, -1, 1 };
int dx2[4] = { 0,1,1,1 };
int dy2[4] = { 1,-1,0,1 };

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

	if (rnk[a] == rnk[b])
	{
		rnk[a]++;
		par[b] = a;
	}
	else if (rnk[a] < rnk[b]) par[a] = b;
	else par[b] = a;
}

bool check(int d)
{
	int i, j, k;
	int nx, ny;

	for (i = 0; i <= n * n; i++)
	{
		par[i] = i;
		rnk[i] = 1;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < 4; k++)
			{
				nx = i + dx2[k];
				ny = j + dy2[k];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

				if (arr[i][j] == '1' && arr[nx][ny] == '1' && dist[i][j] <= d && dist[nx][ny] <= d) union_(num[i][j], num[nx][ny]);
			}
		}
	}

	return find(num[0][0]) == find(num[n - 1][n - 1]);
}

int main()
{
	int i, j;
	int a, b;
	queue<pair<int, int>> que;
	int size;
	int d;
	int nx, ny;
	int s, e;
	int mid;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		que.push(make_pair(a - 1, b - 1));
		visited[a - 1][b - 1] = true;
	}
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	d = 0;
	visited[0][0] = true;
	visited[n - 1][n - 1] = true;
	while (!que.empty())
	{
		size = que.size();
		while (size--)
		{
			a = que.front().first;
			b = que.front().second;
			que.pop();

			dist[a][b] = d;

			for (i = 0; i < 4; i++)
			{
				nx = a + dx[i];
				ny = b + dy[i];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				
				if (!visited[nx][ny])
				{
					visited[nx][ny] = true;
					que.push(make_pair(nx, ny));
				}
			}
		}

		d++;
	}

	a = 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			num[i][j] = a++;
		}
	}

	ans = -1;
	s = 0;
	e = n * n;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (check(mid))
		{
			ans = mid;
			e = mid - 1;
		}
		else s = mid + 1;
	}

	cout << ans;
}
