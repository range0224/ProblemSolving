#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
vector<long long> v;
long long sum;

int main()
{
	int t;
	int i;
	long long x;
	long long a, b;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> x;

		v.push_back(x);
		sum += v[i];
	}

	sort(v.begin(), v.end());

	cin >> t;
	while (t--)
	{
		cin >> a >> b;

		auto it = lower_bound(v.begin(), v.end(), a);
		
		if (it == v.end())
		{
			cout << (a - v[n - 1]) + max(0LL, b - (sum - v[n - 1])) << '\n';
		}
		else if (it == v.begin())
		{
			cout << max(0LL, b - (sum - v[0])) << '\n';
		}
		else
		{
			ans = max(0LL, b - (sum - *it));

			it--;

			ans = min(ans, a - *it + max(0LL, b - (sum - *it)));

			cout << ans << '\n';
		}
	}
}
