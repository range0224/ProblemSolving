#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 320;
int n;
int arr[100010];
int arr2[100010];
vector<pair<pair<int, int>, pair<int, int>>> v;
long long ans[100010];
long long tree[2][100010];
int cnt[2][100010];

bool comp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

void update(int idx, int value, int t)
{
	while (idx <= 100000)
	{
		tree[t][idx] += value;
		idx += (idx & (-idx));
	}
}

long long get(int idx, int t)
{
	long long ret = 0;

	while (idx >= 1)
	{
		ret += tree[t][idx];
		idx -= (idx & (-idx));
	}

	return ret;
}

int get_sqrt(int x)
{
	int s, e;
	int mid;
	int ret = 0;

	s = 0;
	e = 1000;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (mid * mid <= x)
		{
			ret = mid;
			s = mid + 1;
		}
		else e = mid - 1;
	}

	return ret;
}

long long get_ans(int x)
{
	long long answer = 0;
	int sqrt = get_sqrt(x);
	int i;

	for (i = sqrt; i >= 1; i--)
	{
		answer += cnt[0][i] * get(x / i, 1);
		answer += cnt[1][i] * get(x / i, 0);
	}

	return answer - get(sqrt, 0) * get(sqrt, 1);
}

int main()
{
	int q;
	int i;
	int a, b, c;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 1; i <= n; i++)
	{
		cin >> arr2[i];
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b >> c;

		v.push_back(make_pair(make_pair(a, b), make_pair(c, i)));
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		cnt[0][arr[i]]++;
		cnt[1][arr2[i]]++;
		update(arr[i], 1, 0);
		update(arr2[i], 1, 1);
	}

	ans[v[0].second.second] = get_ans(v[0].second.first);

	for (i = 1; i < q; i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			cnt[0][arr[a]]++;
			cnt[1][arr2[a]]++;
			update(arr[a], 1, 0);
			update(arr2[a], 1, 1);
		}
		while (b < v[i].first.second)
		{
			b++;

			cnt[0][arr[b]]++;
			cnt[1][arr2[b]]++;
			update(arr[b], 1, 0);
			update(arr2[b], 1, 1);
		}
		while (a < v[i].first.first)
		{
			cnt[0][arr[a]]--;
			cnt[1][arr2[a]]--;
			update(arr[a], -1, 0);
			update(arr2[a], -1, 1);

			a++;
		}
		while (b > v[i].first.second)
		{
			cnt[0][arr[b]]--;
			cnt[1][arr2[b]]--;
			update(arr[b], -1, 0);
			update(arr2[b], -1, 1);

			b--;
		}

		ans[v[i].second.second] = get_ans(v[i].second.first);
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
