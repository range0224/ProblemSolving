#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 19;
const int len = 1 << 18;
int n;
int arr[200010];
vector<pair<int, int>> query;
int s[200010];
int e[200010];
int ans[200010];
vector<pair<int, int>> v;
vector<pair<int, int>> tv;
int tree[SIZE];

void init_tree()
{
	int i;

	for (i = 0; i < SIZE; i++) tree[i] = 0;
}

void update(int idx)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx]++;
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i;
	int a, b;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		v.push_back(make_pair(arr[i], i));
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));
	}

	for (i = 0; i < q; i++)
	{
		s[i] = 1;
		e[i] = 200000;
	}

	sort(v.begin(), v.end());

	while (1)
	{
		tv.clear();

		for (i = 0; i < q; i++)
		{
			if (s[i] > e[i]) continue;

			tv.push_back(make_pair((s[i] + e[i]) / 2, i));
		}

		if (tv.empty()) break;

		sort(tv.begin(), tv.end());

		init_tree();

		idx = v.size() - 1;
		for (i = tv.size() - 1; i >= 0; i--)
		{
			while (idx >= 0 && v[idx].first >= tv[i].first)
			{
				update(v[idx].second);
				idx--;
			}

			a = query[tv[i].second].first;
			b = query[tv[i].second].second;
			if (get(1, 0, len - 1, a, b) >= tv[i].first)
			{
				ans[tv[i].second] = tv[i].first;
				s[tv[i].second] = tv[i].first + 1;
			}
			else e[tv[i].second] = tv[i].first - 1;
		}
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
