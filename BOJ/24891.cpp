#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
string arr[30];
string arr2[10];
bool visited[30];
bool flag;

bool check()
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr2[i][j] != arr2[j][i]) return false;
		}
	}

	return true;
}

void recur(int cur)
{
	int i;

	if (flag) return;

	if (cur == n)
	{
		if (check())
		{
			for (i = 0; i < n; i++)
			{
				cout << arr2[i] << '\n';
			}
			flag = true;
		}
		return;
	}

	for (i = 0; i < m; i++)
	{
		if (visited[i]) continue;

		visited[i] = true;
		arr2[cur] = arr[i];
		recur(cur + 1);
		visited[i] = false;
	}
}

int main()
{
	int i;

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + m);

	recur(0);

	if (!flag) cout << "NONE";
}
