#include<iostream>
using namespace std;

int n;
int arr[110][110];
int num[110][110];
int par[10010];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

bool in_range(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < n;
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

void init()
{
	int i;

	for (i = 0; i < 10010; i++) par[i] = i;
}

bool can_go(int s, int e)
{
	int i, j, k;
	int nx, ny;

	if (arr[0][0] < s || arr[0][0] > e) return false;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < 4; k++)
			{
				nx = i + dx[k];
				ny = j + dy[k];

				if (!in_range(nx, ny) || arr[i][j] < s || arr[i][j] > e || arr[nx][ny] < s || arr[nx][ny] > e) continue;

				union_(num[nx][ny], num[i][j]);
			}
		}
	}

	return find(num[0][0]) == find(num[n - 1][n - 1]);
}

bool check(int x)
{
	int i;

	for (i = 0; i <= 200 - x; i++)
	{
		init();

		if (can_go(i, i + x)) return true;
	}

	return false;
}

int main()
{
	int i, j;
	int s, e;
	int mid;
	int ans;
	int x;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	x = 1;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			num[i][j] = x++;
		}
	}

	ans = 200;
	s = 0;
	e = 200;
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
