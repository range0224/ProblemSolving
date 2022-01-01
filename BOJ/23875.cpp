#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int n, m, k;
vector<pair<int, int>> v;
long long arr[200010];

int main()
{
	int i, j;
	int a, b;
	priority_queue<long long> pq;
	long long ans;
	vector<pair<int, int>> tv;
	int idx;
	long long sum;
	long long mx;

	cin >> n >> m >> k;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(2 * a, b));
	}
	for (i = 0; i < m; i++)
	{
		cin >> arr[i];

		arr[i] *= 2;
	}

	arr[m] = -4000000000LL;
	arr[m + 1] = 4000000000LL;

	m += 2;

	sort(v.begin(), v.end());
	sort(arr, arr + m);

	idx = 0;
	for (i = 0; i < m; i++)
	{
		tv.clear();
		while (idx < v.size() && v[idx].first < arr[i + 1])
		{
			tv.push_back(v[idx++]);
		}

		sum = 0;
		for (j = 0; j < tv.size(); j++)
		{
			if (arr[i + 1] - tv[j].first <= tv[j].first - (tv[0].first + (tv[0].first - arr[i] - 1))) break;

			sum += tv[j].second;
		}

		a = j;
		mx = sum;
		for (j = 1; j < tv.size(); j++)
		{
			sum -= tv[j - 1].second;
			while (a < tv.size() && arr[i + 1] - tv[a].first > tv[a].first - (tv[j].first + (tv[j].first - arr[i] - 1))) sum += tv[a++].second;

			mx = max(mx, sum);
		}

		sum = 0;
		for (j = 0; j < tv.size(); j++)
		{
			sum += tv[j].second;
		}

		pq.push(mx);
		pq.push(sum - mx);
	}

	ans = 0;
	for (i = 0; i < k; i++)
	{
		ans += pq.top();
		pq.pop();
	}

	cout << ans;
}
