#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;
map<int, vector<int>> mv;
map<int, bool> visited;
vector<int> tv;
int cnt;

void dfs(int cur)
{
	int i;

	tv.push_back(cur);
	visited[cur] = true;
	for (i = 0; i < mv[cur].size(); i++)
	{
		if (visited.find(mv[cur][i]) != visited.end()) continue;

		dfs(mv[cur][i]);
	}
	cnt += mv[cur].size();
}

int main()
{
	int i, j;
	int a, b;
	long long ans = 0;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a, b));

		mv[a].push_back(b);
		mv[b].push_back(a);

		ans += a;
		ans += b;
	}

	for (i = 0; i < v.size(); i++)
	{
		if (visited.find(v[i].first) != visited.end()) continue;

		cnt = 0;
		tv.clear();
		dfs(v[i].first);

		if (2 * tv.size() == cnt)
		{
			for (j = 0; j < tv.size(); j++)
			{
				ans -= tv[j];
			}
		}
		else
		{
			sort(tv.begin(), tv.end());
			for (j = 0; j < tv.size() - 1; j++)
			{
				ans -= tv[j];
			}
		}
	}

	cout << ans;
}
