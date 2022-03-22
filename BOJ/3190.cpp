#include<iostream>
#include<vector>
using namespace std;

int n, m, k;
int arr[110][110];
vector<pair<int, char>> query;
vector<pair<int, int>> v;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

bool in_range(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void print()
{
	int i, j;

	cout << '\n';
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	int i;
	int a, b;
	char c;
	int dir;
	int idx;
	int t;
	int nx, ny;

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		arr[a][b] = 1;
	}
	cin >> k;
	for (i = 0; i < k; i++)
	{
		cin >> a >> c;

		query.push_back(make_pair(a, c));
	}
	
	t = 0;
	dir = 0;
	idx = 0;
	v.push_back(make_pair(1, 1));
	arr[1][1] = 2;
	while (true)
	{
		if (idx < k && query[idx].first == t)
		{
			if (query[idx].second == 'L') dir = (dir + 3) % 4;
			else dir = (dir + 1) % 4;

			idx++;
		}
		
		nx = v[0].first + dx[dir];
		ny = v[0].second + dy[dir];

		if (!in_range(nx, ny) || arr[nx][ny] == 2) break;

		if (arr[nx][ny] == 1) v.push_back(v.back());
		else arr[v.back().first][v.back().second] = 0;

		arr[nx][ny] = 2;

		for (i = v.size() - 1; i >= 1; i--)
		{
			v[i].first = v[i - 1].first;
			v[i].second = v[i - 1].second;
		}
		v[0].first = nx;
		v[0].second = ny;

		t++;
	}

	cout << t + 1;
}
