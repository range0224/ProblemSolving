#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	int n, m;
	int i;
	long long j;
	int x;
	int cnt;
	vector<pair<int, int>> v;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	while (cin >> n)
	{
		cin >> m;

		x = m;
		v.clear();
		for (i = 2; i * i <= m; i++)
		{
			cnt = 0;
			while (x % i == 0)
			{
				x /= i;
				cnt++;
			}

			if (cnt) v.push_back(make_pair(i, cnt));
		}

		if (x != 1) v.push_back(make_pair(x, 1));

		ans = 1;
		for (i = 0; i < v.size(); i++)
		{
			cnt = 0;
			for (j = v[i].first; j <= n; j *= v[i].first)
			{
				cnt += n / j;
			}

			for (j = 0; j < min(v[i].second, cnt); j++) ans *= v[i].first;
		}

		cout << ans << '\n';
	}
}
