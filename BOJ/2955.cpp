#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

char arr[10][10];
bool visited[10];
bool valid;

bool is_in(int x, int y, int num)
{
	int i, j;

	for (i = 3 * x; i < 3 * (x + 1); i++)
	{
		for (j = 3 * y; j < 3 * (y + 1); j++)
		{
			if (arr[i][j] == num + '0') return true;
		}
	}

	return false;
}

bool check(int x, int y, int num)
{
	int i;

	for (i = 0; i < 9; i++)
	{
		if (arr[x][i] == num + '0' || arr[i][y] == num + '0') return false;
	}

	return true;
}

bool cross_hatching(int num)
{
	int i, j, k, l;
	vector<pair<int, int>> v;
	bool ret = false;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (is_in(i, j, num)) continue;

			v.clear();
			for (k = 3 * i; k < 3 * (i + 1); k++)
			{
				for (l = 3 * j; l < 3 * (j + 1); l++)
				{
					if (arr[k][l] == '.' && check(k, l, num)) v.push_back(make_pair(k, l));
				}
			}

			if (v.size() == 1)
			{
				arr[v[0].first][v[0].second] = num + '0';
				ret = true;
			}
			else if (v.size() == 0)
			{
				valid = false;
				return false;
			}
		}
	}

	return ret;
}

int main()
{
	int i, j, k, l;
	bool flag;

	for (i = 0; i < 9; i++)
	{
		cin >> arr[i];
	}

	for (i = 0; i < 9; i++)
	{
		memset(visited, false, sizeof(visited));

		for (j = 0; j < 9; j++)
		{
			if (arr[i][j] == '.') continue;

			if (visited[arr[i][j] - '0'])
			{
				cout << "ERROR";
				return 0;
			}

			visited[arr[i][j] - '0'] = true;
		}
	}

	for (j = 0; j < 9; j++)
	{
		memset(visited, false, sizeof(visited));

		for (i = 0; i < 9; i++)
		{
			if (arr[i][j] == '.') continue;

			if (visited[arr[i][j] - '0'])
			{
				cout << "ERROR";
				return 0;
			}

			visited[arr[i][j] - '0'] = true;
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			memset(visited, false, sizeof(visited));

			for (k = 3 * i; k < 3 * (i + 1); k++)
			{
				for (l = 3 * j; l < 3 * (j + 1); l++)
				{
					if (arr[k][l] == '.') continue;

					if (visited[arr[k][l] - '0'])
					{
						cout << "ERROR";
						return 0;
					}

					visited[arr[k][l] - '0'] = true;
				}
			}
		}
	}

	valid = true;
	while (1)
	{
		flag = false;
		for (i = 1; i <= 9; i++)
		{
			flag |= cross_hatching(i);
		}

		if (!valid)
		{
			cout << "ERROR";
			return 0;
		}
		if (!flag) break;
	}

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			cout << arr[i][j];
		}
		cout << '\n';
	}
}
