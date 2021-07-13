#include<iostream>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int INF = 1 << 29;
int INIT;
int n, m;
int arr[10][10];
int dp[10][10][100000];
map<long long, int> mp;

void to_normal(int *con)
{
	int i;
	bool visited[12] = { 0 };
	int trans[12] = { 0 };
	int idx = 1;

	for (i = 0; i < m; i++)
	{
		if (!con[i]) continue;

		if (!visited[con[i]]) trans[con[i]] = idx++;
		visited[con[i]] = true;
	}

	for (i = 0; i < m; i++)
	{
		if (!con[i]) continue;

		con[i] = trans[con[i]];
	}
}

int recur(int x, int y, int* connection)
{
	int con[10] = { 0 };
	int i;
	int t;
	int ret = INF;
	bool flag;
	long long state;
	long long mul;

	if (y == m)
	{
		x++;
		y = 0;
	}
	if (x == n)
	{
		for (i = 0; i < m; i++)
		{
			if (connection[i] == 2) return INF;
		}
		return 0;
	}

	state = 0;
	mul = 1;
	for (i = 0; i < m; i++)
	{
		state += mul * connection[i];
		mul *= 10;
	}

	if (mp.find(state) == mp.end()) mp[state] = mp.size() + 1;

	state = mp[state];
	if (dp[x][y][state] != INIT) return dp[x][y][state];

	for (i = 0; i < m; i++) con[i] = connection[i + 1];
	con[m - 1] = 10;
	if (connection[0])
	{
		t = connection[0];
		for (i = 0; i < m; i++)
		{
			if (con[i] == t) con[i] = 10;
		}
	}
	if (y != 0 && connection[m - 1])
	{
		t = connection[m - 1];
		for (i = 0; i < m; i++)
		{
			if (con[i] == t) con[i] = 10;
		}
	}
	to_normal(con);
	ret = min(ret, recur(x, y + 1, con) + arr[x][y]);

	if (connection[0])
	{
		flag = false;
		for (i = 1; i < m; i++)
		{
			if (connection[i] == connection[0]) flag = true;
		}

		if (!flag)
		{
			for (i = 1; i < m; i++)
			{
				if (connection[i]) return dp[x][y][state] = ret;
			}

			ret = min(ret, 0);
			return dp[x][y][state] = ret;
		}
	}
	else flag = true;

	if (flag)
	{
		for (i = 0; i < m; i++) con[i] = connection[i + 1];
		con[m - 1] = 0;
		to_normal(con);
		ret = min(ret, recur(x, y + 1, con));
	}

	return dp[x][y][state] = ret;
}

int main()
{
	int i, j;
	int connection[10] = { 0 };

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}

	memset(dp, 110, sizeof(dp));
	INIT = dp[0][0][0];

	cout << recur(0, 0, connection);
}
