#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

int n, m;
int par[100010];
set<int> s, e;
long long dist[100010][2];

int find(int x)
{
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	par[a] = b;
}

int main()
{
	int t;
	int i;
	int a, b;
	long long ans;

	cin >> t;
	while (t--)
	{
		cin >> n >> m;

		for (i = 1; i <= n; i++) par[i] = i;

		for (i = 0; i < m; i++)
		{
			cin >> a >> b;

			union_(a, b);
		}

		s.clear();
		e.clear();

		for (i = 1; i <= n; i++)
		{
			if (find(i) == find(1)) s.insert(i);
			if (find(i) == find(n)) e.insert(i);
		}

		for (i = 1; i <= n; i++)
		{
			dist[i][0] = 1000000000000000000LL;
			dist[i][1] = 1000000000000000000LL;
		}

		for (i = 1; i <= n; i++)
		{
			auto it = s.lower_bound(i);
			auto it2 = it;
			
			if(it != s.begin()) it--;

			if (it != s.end()) dist[find(i)][0] = min(dist[find(i)][0], 1LL * (i - *it) * (i - *it));
			if (it2 != s.end()) dist[find(i)][0] = min(dist[find(i)][0], 1LL * (i - *it2) * (i - *it2));

			it = e.lower_bound(i);
			it2 = it;

			if (it != e.begin()) it--;

			if (it != e.end()) dist[find(i)][1] = min(dist[find(i)][1], 1LL * (i - *it) * (i - *it));
			if (it2 != e.end()) dist[find(i)][1] = min(dist[find(i)][1], 1LL * (i - *it2) * (i - *it2));
		}

		ans = dist[find(n)][0];
		for (i = 1; i <= n; i++)
		{
			ans = min(ans, dist[find(i)][0] + dist[find(i)][1]);
		}

		cout << ans << '\n';
	}
}
