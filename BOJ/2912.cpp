#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

int n;
int arr[300010];
vector<int> v[10010];

bool check(int s, int e, int v)
{
	int i;
	int cnt = 0;

	for (i = s; i <= e; i++)
	{
		if (arr[i] == v) cnt++;
	}

	return 2 * cnt > e - s + 1;
}

int main()
{
	int q;
	int i, j;
	int a, b, c;
	int ans;
	int cnt;
	int value;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> c;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		v[arr[i]].push_back(i);
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		ans = -1;
		for (j = 0; j < 50; j++)
		{
			value = arr[rand() % (b - a + 1) + a];

			cnt = upper_bound(v[value].begin(), v[value].end(), b) - lower_bound(v[value].begin(), v[value].end(), a);

			if (2 * cnt > b - a + 1)
			{
				ans = value;
				break;
			}
		}

		if (ans != -1) cout << "yes " << ans << '\n';
		else cout << "no\n";
	}
}
