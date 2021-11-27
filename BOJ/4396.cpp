#include<iostream>
using namespace std;

int n;
char arr[15][15];
char user[15][15];
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool in_range(int x, int y)
{
	return x >= 0 && x < n&& y >= 0 && y < n;
}

int main()
{
	int i, j, k;
	bool die;
	int cnt;
	int nx, ny;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < n; i++)
	{
		cin >> user[i];
	}

	die = false;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] == '*' && user[i][j] == 'x') die = true;
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] == '*')
			{
				if (die) cout << '*';
				else cout << '.';
			}
			else
			{
				if (user[i][j] == '.') cout << '.';
				else
				{
					cnt = 0;
					for (k = 0; k < 8; k++)
					{
						nx = i + dx[k];
						ny = j + dy[k];

						if (in_range(nx, ny) && arr[nx][ny] == '*') cnt++;
					}
					cout << cnt;
				}
			}
		}
		cout << '\n';
	}
}
