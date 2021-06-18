#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 1000;
int n;
int arr[1000010];
vector<pair<pair<int, int>, int>> v;
vector<pair<int, int>> tv, tv2;
int cnt[1000010];
int ans[1000010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

int main()
{
	int i;
	int a, b;
	int q;
	int answer = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	for (i = 1; i <= n; i++)
	{
		tv.push_back(make_pair(arr[i], i));
	}

	sort(tv.begin(), tv.end());

	tv2.push_back(make_pair(0, tv[0].second));
	for (i = 1; i < tv.size(); i++)
	{
		if (tv[i].first == tv[i - 1].first) tv2.push_back(make_pair(tv2[i - 1].first, tv[i].second));
		else tv2.push_back(make_pair(tv2[i - 1].first + 1, tv[i].second));
	}

	for (i = 0; i < tv2.size(); i++)
	{
		arr[tv2[i].second] = tv2[i].first;
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		if (!cnt[arr[i]]) answer++;

		cnt[arr[i]]++;
	}
	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			if (!cnt[arr[a]]) answer++;

			cnt[arr[a]]++;
		}
		while (b < v[i].first.second)
		{
			b++;

			if (!cnt[arr[b]]) answer++;

			cnt[arr[b]]++;
		}
		while (a < v[i].first.first)
		{
			cnt[arr[a]]--;

			if (!cnt[arr[a]]) answer--;

			a++;
		}
		while (b > v[i].first.second)
		{
			cnt[arr[b]]--;

			if (!cnt[arr[b]]) answer--;

			b--;
		}

		ans[v[i].second] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
