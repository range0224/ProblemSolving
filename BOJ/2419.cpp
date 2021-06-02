#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

const int INF = 1000000000;
int n, m;
vector<int> v;
int dp[310][310][2];

int recur(int s, int e, int pos, int cnt)
{
	int ret;

	if (cnt == 0) return 0;
	if (s > e) return INF;

	if (dp[s][e][pos] != -1) return dp[s][e][pos];

	ret = INF;
	if (pos == 0)
	{
		if (s != 0) ret = min(ret, recur(s - 1, e, 0, cnt - 1) + cnt * (v[s] - v[s - 1]));
		if (e != v.size() - 1) ret = min(ret, recur(s, e + 1, 1, cnt - 1) + cnt * (v[e + 1] - v[s]));
	}
	else
	{
		if (s != 0) ret = min(ret, recur(s - 1, e, 0, cnt - 1) + cnt * (v[e] - v[s - 1]));
		if (e != v.size() - 1) ret = min(ret, recur(s, e + 1, 1, cnt - 1) + cnt * (v[e + 1] - v[e]));
	}

	return dp[s][e][pos] = ret;
}

int main()
{
	int i;
	int x;
	int idx;
	int ans = 0;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> x;

		v.push_back(x);
	}

	v.push_back(0);

	sort(v.begin(), v.end());

	for (i = 0; i < v.size(); i++)
	{
		if (v[i] == 0) break;
	}

	idx = i;

	for (i = 0; i <= n; i++)
	{
		memset(dp, -1, sizeof(dp));

		ans = max(ans, i * m - recur(idx, idx, 0, i));
	}

	cout << ans;
}
