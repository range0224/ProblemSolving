#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
vector<pair<int, int>> v1, v2;
vector<pair<int, int>> l, r;
long long ans;

void recur(int s1, int e1, int s2, int e2)
{
	int mid;
	int i;
	long long a, b;
	long long x;
	long long mx;
	int idx;

	if (s1 > e1) return;

	mid = (s1 + e1) / 2;

	mx = -(1LL << 60);
	idx = s2;
	for (i = s2; i <= e2; i++)
	{
		a = r[i].first - l[mid].first;
		b = r[i].second - l[mid].second;

		if (a < 0 && b < 0) x = 0;
		else x = a * b;

		if (mx < x)
		{
			mx = x;
			idx = i;
		}
	}

	ans = max(ans, mx);

	recur(s1, mid - 1, s2, idx);
	recur(mid + 1, e1, idx, e2);
}

int main()
{
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v1.push_back(make_pair(a, b));
	}
	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		v2.push_back(make_pair(a, b));
	}

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());

	l.push_back(v1[0]);
	for (i = 1; i < v1.size(); i++)
	{
		if (v1[i].second < l.back().second) l.push_back(v1[i]);
	}

	r.push_back(v2.back());
	for (i = v2.size() - 2; i >= 0; i--)
	{
		if (v2[i].second > r.back().second) r.push_back(v2[i]);
	}
	reverse(r.begin(), r.end());

	recur(0, l.size() - 1, 0, r.size() - 1);

	cout << ans;
}
