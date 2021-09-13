#include<iostream>
#include<string>
#include<vector>
using namespace std;

int n;
string str;
char arr[20][20];
bool light[20][20];
vector<pair<pair<int, int>, int>> v;
int x, y, dir;
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int dx2[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
int dy2[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };

bool in_range(int x, int y)
{
	return x >= 0 && x < n&& y >= 0 && y < n;
}

int main()
{
	int i, j;
	int nx, ny;
	bool flag;

	cin >> n;
	cin >> str;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] == 'Z')
			{
				v.push_back(make_pair(make_pair(i, j), 0));
			}
		}
	}

	x = 0;
	y = 0;
	dir = 0;
	for (i = 0; i < str.length(); i++)
	{
		if (str[i] == 'F')
		{
			nx = x + dx[dir];
			ny = y + dy[dir];

			if (in_range(nx, ny))
			{
				x = nx;
				y = ny;
			}
		}
		else if (str[i] == 'L') dir = (dir + 1) % 4;
		else dir = (dir + 3) % 4;

		if (arr[x][y] == 'S')
		{
			for (j = 0; j < 9; j++)
			{
				nx = x + dx2[j];
				ny = y + dy2[j];

				if (in_range(nx, ny)) light[nx][ny] = true;
			}
		}

		flag = false;
		for (j = 0; j < v.size(); j++)
		{
			if (v[j].first.first == x && v[j].first.second == y) flag = true;

			nx = v[j].first.first + dx[v[j].second];
			ny = v[j].first.second + dy[v[j].second];

			if(!in_range(nx, ny)) v[j].second = (v[j].second + 2) % 4;
			else
			{
				v[j].first.first = nx;
				v[j].first.second = ny;
			}

			if (v[j].first.first == x && v[j].first.second == y) flag = true;
		}

		if (!light[x][y] && flag)
		{
			cout << "Aaaaaah!";
			return 0;
		}
	}

	cout << "Phew...";
}
