#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
int n, k;
int arr[100010];
vector<pair<pair<int, int>, int>> v;
int prefix[100010];
long long ans[100010];
int cnt[3000010];

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
	long long answer = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> k;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a - 1, b), i));
	}

	sort(v.begin(), v.end(), comp);

	for (i = 1; i <= n; i++)
	{
		prefix[i] = prefix[i - 1] ^ arr[i];
	}

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		answer += cnt[prefix[i] ^ k];
		cnt[prefix[i]]++;
	}
	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;
			answer += cnt[prefix[a] ^ k];
			cnt[prefix[a]]++;
		}
		while (b < v[i].first.second)
		{
			b++;
			answer += cnt[prefix[b] ^ k];
			cnt[prefix[b]]++;
		}
		while (a < v[i].first.first)
		{
			cnt[prefix[a]]--;
			answer -= cnt[prefix[a] ^ k];
			a++;
		}
		while (b > v[i].first.second)
		{
			cnt[prefix[b]]--;
			answer -= cnt[prefix[b] ^ k];
			b--;
		}

		ans[v[i].second] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
