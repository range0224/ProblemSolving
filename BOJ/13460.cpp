#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
char arr[20][20];
int ans = 100000;

bool in_range(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}

void cpy(char a[20][20], char b[20][20])
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

void rotate()
{
	int i, j;
	char arr2[20][20];

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			arr2[m - j - 1][i] = arr[i][j];
		}
	}

	swap(n, m);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			arr[i][j] = arr2[i][j];
		}
	}
}

void drop()
{
	int i, j;
	int rx, ry, bx, by;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (arr[i][j] == 'R')
			{
				rx = i;
				ry = j;

				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'B')
			{
				bx = i;
				by = j;

				arr[i][j] = '.';
			}
		}
	}

	if (rx > bx)
	{
		while (in_range(rx, ry) && arr[rx][ry] == '.') rx++;

		if (in_range(rx, ry) && arr[rx][ry] == 'O');
		else arr[rx - 1][ry] = 'R';

		while (in_range(bx, by) && arr[bx][by] == '.') bx++;

		if (in_range(bx, by) && arr[bx][by] == 'O');
		else arr[bx - 1][by] = 'B';
	}
	else
	{
		while (in_range(bx, by) && arr[bx][by] == '.') bx++;

		if (in_range(bx, by) && arr[bx][by] == 'O');
		else arr[bx - 1][by] = 'B';

		while (in_range(rx, ry) && arr[rx][ry] == '.') rx++;

		if (in_range(rx, ry) && arr[rx][ry] == 'O');
		else arr[rx - 1][ry] = 'R';
	}
}

int check()
{
	int i, j;
	bool r, b;

	r = false;
	b = false;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (arr[i][j] == 'R') r = true;
			else if (arr[i][j] == 'B') b = true;
		}
	}

	if (!r && b) return 1;
	else if (!r || !b) return -1;
	else return 0;
}

void recur(int cur)
{
	int i;
	char arr2[20][20];
	int flag;

	flag = check();
	if (flag == 1)
	{
		ans = min(ans, cur);
		return;
	}
	else if (flag == -1) return;

	if (cur == 10) return;

	rotate();
	for (i = 0; i < 2; i++)
	{
		rotate();
		rotate();

		cpy(arr2, arr);

		drop();

		recur(cur + 1);

		cpy(arr, arr2);
	}
	rotate();
	rotate();
	rotate();
}

int main()
{
	int i, j;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	recur(0);
	rotate();
	recur(0);

	if (ans == 100000) ans = -1;

	cout << ans;
}
