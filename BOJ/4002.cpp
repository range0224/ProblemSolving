#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int n, m;
vector<int> v[100010];
int leader[100010];
multiset<int> s[100010];
long long sum[100010];
long long ans;

int dfs(int cur)
{
	int idx;
	int i;
	vector<int> tv;

	for (i = 0; i < v[cur].size(); i++)
	{
		tv.push_back(dfs(v[cur][i]));
	}

	idx = cur;
	for (i = 0; i < tv.size(); i++)
	{
		if (s[idx].size() < s[tv[i]].size())
		{
			for (auto it = s[idx].begin(); it != s[idx].end(); it++)
			{
				s[tv[i]].insert(*it);
				sum[tv[i]] += *it;
			}
			idx = tv[i];
		}
		else
		{
			for (auto it = s[tv[i]].begin(); it != s[tv[i]].end(); it++)
			{
				s[idx].insert(*it);
				sum[idx] += *it;
			}
		}
	}

	while (sum[idx] > m)
	{
		sum[idx] -= *s[idx].rbegin();
		s[idx].erase(s[idx].find(*s[idx].rbegin()));
	}

	ans = max(ans, (long long)(leader[cur] * s[idx].size()));

	return idx;
}

int main()
{
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> a >> b >> leader[i];

		v[a].push_back(i);
		s[i].insert(b);
		sum[i] = b;
	}

	dfs(1);

	cout << ans;
}
