#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n, m;
long long arr[100010];
vector<pair<pair<int, int>, int>> v;
long long cnt[1000010];
long long ans[100010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
	else return a.first.second < b.first.second;
}

int main()
{
	int i;
	int a, b;
	long long answer = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < m; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		answer -= cnt[arr[i]] * cnt[arr[i]] * arr[i];
		cnt[arr[i]]++;
		answer += cnt[arr[i]] * cnt[arr[i]] * arr[i];
	}
	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			answer -= cnt[arr[a]] * cnt[arr[a]] * arr[a];
			cnt[arr[a]]++;
			answer += cnt[arr[a]] * cnt[arr[a]] * arr[a];
		}
		while (b < v[i].first.second)
		{
			b++;

			answer -= cnt[arr[b]] * cnt[arr[b]] * arr[b];
			cnt[arr[b]]++;
			answer += cnt[arr[b]] * cnt[arr[b]] * arr[b];
		}
		while (a < v[i].first.first)
		{
			answer -= cnt[arr[a]] * cnt[arr[a]] * arr[a];
			cnt[arr[a]]--;
			answer += cnt[arr[a]] * cnt[arr[a]] * arr[a];

			a++;
		}
		while (b > v[i].first.second)
		{
			answer -= cnt[arr[b]] * cnt[arr[b]] * arr[b];
			cnt[arr[b]]--;
			answer += cnt[arr[b]] * cnt[arr[b]] * arr[b];

			b--;
		}
		
		ans[v[i].second] = answer;
	}

	for (i = 0; i < m; i++)
	{
		cout << ans[i] << '\n';
	}
}
