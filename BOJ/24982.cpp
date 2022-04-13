#include<iostream>
#include<vector>
using namespace std;

int n, m;
int arr[110];
vector<int> v[110];

bool dfs(int cur, int val)
{
	int i;

	if (arr[cur] >= val)
	{
		arr[cur] -= val;

		return true;
	}

	if (v[cur].empty()) return false;

	for (i = 0; i < v[cur].size(); i++)
	{
		if (!dfs(v[cur][i], val - arr[cur])) return false;
	}

	arr[cur] = 0;

	return true;
}

int main()
{
	int i, j;
	int a, b, c;
	int t;
	int arr2[110];
	int ans;

    cin >> n;
	for (i = 1; i <= n; i++)
	{
        cin >> arr[i];
	}
    cin >> m;
	for (i = 0; i < m; i++)
	{
        cin >> a >> b;
		for (j = 0; j < b; j++)
		{
            cin >> c;

			v[a].push_back(c);
		}
	}

	ans = 0;
	while (1)
	{
		t = 100;
		while (t > 0)
		{
			for (i = 1; i <= n; i++) arr2[i] = arr[i];

			if (dfs(n, t)) break;

			for (i = 1; i <= n; i++) arr[i] = arr2[i];
			t /= 2;
		}

		if (t == 0) break;

		ans += t;
	}

    cout << ans;
}
