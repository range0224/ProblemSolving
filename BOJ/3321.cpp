#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
char arr[1510];
int prefix[2][1510];
pair<int, int> grid[2][1510];
bool used[1510];

int main()
{
	int i, j;
	int ans = 0;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;

	for (j = 0; j < m; j++)
	{
		grid[1][j].first = 0;
		grid[1][j].second = j;
	}

	for (i = 0; i < n; i++)
	{
		cin >> arr;

		memset(used, false, sizeof(used));
		for (j = 0; j < m; j++)
		{
			if (arr[j] == '0') prefix[i % 2][j] = 0;
			else
			{
				used[j] = true;
				prefix[i % 2][j] = prefix[!(i % 2)][j] + 1;
			}
		}

		idx = 0;
		for (j = 0; j < m; j++)
		{
			if (used[grid[!(i % 2)][j].second])
			{
				grid[i % 2][idx] = grid[!(i % 2)][j];
				grid[i % 2][idx].first++;
				idx++;
			}
		}

		for (j = 0; j < m; j++)
		{
			if (!used[grid[!(i % 2)][j].second])
			{
				grid[i % 2][idx] = grid[!(i % 2)][j];
				grid[i % 2][idx].first = 0;
				idx++;
			}
		}

		for (j = 0; j < m; j++) ans = max(ans, grid[i % 2][j].first * (j + 1));
	}

	cout << ans;
}
