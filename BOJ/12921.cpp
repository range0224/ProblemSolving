#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
int n, x0, a, b;
vector<int> query;
vector<pair<int, int>> v;
int s[1010];
int e[1010];
int ans[1010];
int prefix[1010];

int main()
{
	int q;
	int i;
	int x;
	int idx;
	bool flag;
	long long prv;
	long long cur;
	int l, r;
	int mid;
	long long answer;
	
	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> x0 >> a >> b;
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> x;
		
		query.push_back(x + 1);
		s[i] = 0;
		e[i] = MOD;
	}

	while (1)
	{
		flag = false;
		v.clear();
		for (i = 0; i < q; i++)
		{
			if (s[i] > e[i]) continue;

			flag = true;
			v.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (!flag) break;

		sort(v.begin(), v.end());

		for (i = 0; i < v.size(); i++) prefix[i] = 0;

		for (i = 0; i < n; i++)
		{
			if (i == 0) cur = x0;
			else cur = (prv * a + b) % MOD;

			idx = -1;
			l = 0;
			r = v.size() - 1;
			while (l <= r)
			{
				mid = (l + r) / 2;

				if (v[mid].first >= cur)
				{
					idx = mid;
					r = mid - 1;
				}
				else l = mid + 1;
			}

			if (idx != -1) prefix[idx]++;

			prv = cur;
		}

		cur = 0;
		for (i = 0; i < v.size(); i++)
		{
			cur += prefix[i];

			if (cur >= query[v[i].second])
			{
				ans[v[i].second] = v[i].first;
				e[v[i].second] = v[i].first - 1;
			}
			else s[v[i].second] = v[i].first + 1;
		}
	}

	answer = 0;
	for (i = 0; i < q; i++)
	{
		answer += ans[i];
	}

	cout << answer;
}
