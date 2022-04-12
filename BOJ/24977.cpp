#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[100010][2];
bool visited[100010];
bool visited2[100010];
int mn;

int dfs(int cur)
{
	int i;
	int ret;

	visited[cur] = true;
	if (visited2[arr[cur][0]])
	{
		visited2[cur] = true;
		return 0;
	}
	else if (visited[arr[cur][0]])
	{
		mn = arr[cur][1];
		visited2[cur] = true;
		return arr[cur][0];
	}
	else
	{
		ret = dfs(arr[cur][0]);

		visited2[cur] = true;

		if (ret == 0) return 0;

		mn = min(mn, arr[cur][1]);

		if (ret == cur) return 0;
		else return ret;
	}
}

int main()
{
	int i;
	long long ans;

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i][0] >> arr[i][1];
	}

	ans = 0;
	for (i = 1; i <= n; i++)
	{
		ans += arr[i][1];

		if (visited[i]) continue;

		mn = 0;
		dfs(i);

		ans -= mn;
	}

	cout << ans;
}
