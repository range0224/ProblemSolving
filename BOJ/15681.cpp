#include<iostream>
#include<vector>
using namespace std;

int n, r;
vector<int> v[100010];
bool visited[100010];
int sz[100010];

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	sz[cur] = 1;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;

		dfs(v[cur][i]);
		sz[cur] += sz[v[cur][i]];
	}
}

int main()
{
	int q;
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> r >> q;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(r);

	while (q--)
	{
		cin >> a;

		cout << sz[a] << '\n';
	}
}
