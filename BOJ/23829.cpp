#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, q;
int arr[100010];
long long ans[100010];
vector<pair<int, int>> v;

int main()
{
	int i;
	long long sum;
	int x;
	int cur;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	for (i = 0; i < q; i++)
	{
		cin >> x;

		v.push_back(make_pair(x, i));
	}

	sort(v.begin(), v.end());

	sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += arr[i];
	}

	cur = 0;
	idx = 0;
	for (i = 0; i < v.size(); i++)
	{
		while (cur < v[i].first)
		{
			sum += idx;
			sum -= n - idx;
			cur++;

			while (idx < n && arr[idx] == cur) idx++;
		}

		ans[v[i].second] = sum;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
