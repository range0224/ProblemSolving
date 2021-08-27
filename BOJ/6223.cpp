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
long long arr[100010];
long long v_arr[100010];
vector<pair<long long, long long>> v;
vector<long long> tv;
bool visited[100010];
long long ans;

int main()
{
	int i, j;
	long long mn;
	long long idx;
	long long sum;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];

		v.push_back(make_pair(arr[i], i));
	}

	sort(v.begin(), v.end());

	for (i = 0; i < n; i++)
	{
		v_arr[v[i].second] = i;
	}

	mn = v[0].first;
	for (i = 0; i < n; i++)
	{
		if (visited[i]) continue;

		tv.clear();

		visited[i] = true;
		tv.push_back(v[i].first);
		idx = v_arr[i];
		while (idx != i)
		{
			visited[idx] = true;
			tv.push_back(v[idx].first);
			idx = v_arr[idx];
		}

		sort(tv.begin(), tv.end());

		sum = 0;
		for (j = 1; j < tv.size(); j++) sum += tv[j];

		ans += min((tv.size() - 1) * tv[0] + sum, (tv.size() - 1) * mn + sum + 2 * (tv[0] + mn));
	}

	cout << ans;
}
