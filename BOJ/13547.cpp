#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 400;
int n;
int arr[100010];
int cnt[1000010];
int ans[100010];
vector<pair<pair<int, int>, int>> v;

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
	else return a.first.second < b.first.second;
}

int main()
{
	int i;
	int q;
	int a, b;
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
		while (a < v[i].first.first)
		{
			cnt[arr[a]]--;
			if (!cnt[arr[a]]) answer--;

			a++;
		}
		while (b < v[i].first.second)
		{
			b++;
			if (!cnt[arr[b]]) answer++;

			cnt[arr[b]]++;
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
