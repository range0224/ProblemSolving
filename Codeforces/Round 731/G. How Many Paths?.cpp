#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
using namespace std;
 
int n, m;
vector<int> v[400010];
bool visited[400010];
bool is_cycle[400010];
stack<int> st;
int ans[400010];
 
void dfs(int cur)
{
	int i;
 
	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;
 
		dfs(v[cur][i]);
	}
 
	st.push(cur);
}
 
void dfs2(int cur)
{
	int i;
 
	ans[cur] = -1;
	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;
 
		dfs2(v[cur][i]);
	}
}
 
void dfs3(int cur)
{
	int i;
 
	if (ans[cur] == -1) return;
 
	ans[cur] = 2;
	visited[cur] = true;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;
 
		dfs3(v[cur][i]);
	}
}
 
int main()
{
	int t;
	int i;
	int a, b;
	int cur;
 
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (i = 0; i < m; i++)
		{
			cin >> a >> b;
 
			v[a].push_back(b);
		}
 
		for (i = 1; i <= n; i++) visited[i] = false;
 
		dfs(1);
 
		for (i = 1; i <= n; i++)
		{
			ans[i] = 0;
			visited[i] = false;
			is_cycle[i] = false;
		}
 
		ans[1] = 1;
		while (!st.empty())
		{
			cur = st.top();
			st.pop();
 
			visited[cur] = true;
			for (i = 0; i < v[cur].size(); i++)
			{
				ans[v[cur][i]]++;
				if (visited[v[cur][i]])
				{
					is_cycle[v[cur][i]] = true;
				}
			}
		}
 
		for (i = 1; i <= n; i++) visited[i] = false;
 
		for (i = 1; i <= n; i++)
		{
			if (is_cycle[i]) dfs2(i);
		}
 
		for (i = 1; i <= n; i++) visited[i] = false;
 
		for (i = 1; i <= n; i++)
		{
			if (ans[i] >= 2) dfs3(i);
		}
 
		for (i = 1; i <= n; i++)
		{
			cout << ans[i] << ' ';
		}
		cout << '\n';
 
		for (i = 1; i <= n; i++) v[i].clear();
	}
}
