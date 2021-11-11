#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

int n;
int top = 1;
int prv[20][200010];
pair<int, int> st[200010];
pair<int, int> s[200010], e[200010], p[200010];
map<int, int> mp;

int check(int s, int e)
{
	int x = (lower_bound(st, st + top, make_pair(e, 0)) - 1)->second;
	int ret = 1;
	int i;

	if (p[x].first <= s) return 0;

	for (i = 19; i >= 0; i--)
	{
		if (p[prv[i][x]].first > s)
		{
			x = prv[i][x];
			ret += 1 << i;
		}
	}

	return ret;
}

int main()
{
	int i, j;
	int idx;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> p[i].first >> p[i].second;
	}

	for (i = 1; i <= n; i++)
	{
		s[i] = make_pair(p[i].first, i);
		e[i] = make_pair(p[i].second, i);
	}

	sort(s + 1, s + n + 1);
	sort(e + 1, e + n + 1);

	x = 0;
	idx = 1;
	for (i = 1; i <= n; i++)
	{
		while (e[idx].first < s[i].first)
		{
			if (p[x].first < p[e[idx].second].first) x = e[idx].second;
			idx++;
		}

		while (st[top - 1].first >= p[s[i].second].second) top--;

		st[top++] = make_pair(p[s[i].second].second, s[i].second);
		prv[0][s[i].second] = x;

		for (j = 1; j < 20; j++) prv[j][s[i].second] = prv[j - 1][prv[j - 1][s[i].second]];
	}

	mp[0] = 0;
	mp[2000000000] = 2000000000;

	cout << check(0, 2000000000) << '\n';
	for (i = 1; i <= n; i++)
	{
		auto it = mp.lower_bound(p[i].first);
		auto it2 = it--;

		if (it->second < p[i].first && p[i].second < it2->first && check(it->second, it2->first) == check(it->second, p[i].first) + 1 + check(p[i].second, it2->first))
		{
			cout << i << ' ';
			mp[p[i].first] = p[i].second;
		}
	}
}
