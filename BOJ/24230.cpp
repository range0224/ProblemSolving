#include<iostream>
#include<vector>
using namespace std;

int n;
int arr[200010];
vector<int> v[200010];

int dfs(int cur, int prv, int c)
{
	int i;
	int ret = 0;

	if (arr[cur] != c)
	{
		ret = 1;
		c = arr[cur];
	}

	for (i = 0; i < v[cur].size(); i++)
	{
		if (v[cur][i] == prv) continue;

		ret += dfs(v[cur][i], cur, c);
	}

	return ret;
}

int main()
{
	int i;
	int a, b;

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;
		
		v[a].push_back(b);
		v[b].push_back(a);
	}

	cout << dfs(1, 0, 0);
}
