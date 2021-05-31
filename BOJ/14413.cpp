#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n;
int arr[500010];
vector<pair<pair<int, int>, int>> v;
vector<pair<int, int>> num, num2;
int cnt[500010];
int ans[500010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
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

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	for (i = 1; i <= n; i++)
	{
		num.push_back(make_pair(arr[i], i));
	}

	sort(num.begin(), num.end());

	num2.push_back(make_pair(1, num[0].second));
	for (i = 1; i < num.size(); i++)
	{
		num2.push_back(make_pair(num2[i - 1].first, num[i].second));
		if (num[i - 1].first != num[i].first) num2[i].first++;
	}

	for (i = 0; i < num2.size(); i++)
	{
		arr[num2[i].second] = num2[i].first;
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		cnt[arr[i]]++;
		if (cnt[arr[i]] == 2) answer++;
		else if (cnt[arr[i]] == 3) answer--;
	}

	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			cnt[arr[a]]++;
			if (cnt[arr[a]] == 2) answer++;
			else if (cnt[arr[a]] == 3) answer--;
		}
		while (b < v[i].first.second)
		{
			b++;

			cnt[arr[b]]++;
			if (cnt[arr[b]] == 2) answer++;
			else if (cnt[arr[b]] == 3) answer--;
		}
		while (a < v[i].first.first)
		{
			cnt[arr[a]]--;
			if (cnt[arr[a]] == 1) answer--;
			else if (cnt[arr[a]] == 2) answer++;

			a++;
		}
		while (b > v[i].first.second)
		{
			cnt[arr[b]]--;
			if (cnt[arr[b]] == 1) answer--;
			else if (cnt[arr[b]] == 2) answer++;

			b--;
		}

		ans[v[i].second] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
