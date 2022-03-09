#include<iostream>
#include<cstring>
using namespace std;

int n;
int arr[510][510];
int prefer[510][510];
bool visited[510];

bool dfs(int x, int start)
{
	int i;

	if (prefer[x][start] <= prefer[x][x]) return true;

	visited[x] = true;
	for (i = 1; arr[x][i] != x; i++)
	{
		if (!visited[arr[x][i]] && dfs(arr[x][i], start)) return true;
	}

	return false;
}

int main()
{
	int i, j;
	int x;

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> arr[i][j];

			prefer[i][arr[i][j]] = j;
		}
	}

	for (i = 1; i <= n; i++)
	{
		memset(visited, false, sizeof(visited));

		for (j = 1; j <= n; j++)
		{
			if (dfs(arr[i][j], i))
			{
				cout << arr[i][j] << '\n';
				break;
			}
		}
	}
}
