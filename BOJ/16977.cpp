#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<pair<int, int>, int> pii;
typedef pair<pair<long long, long long>, pair<long long, long long>> pll;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
vector<pii> query;
vector<pair<int, int>> v;
vector<pair<int, int>> tv;
pll tree[SIZE];
int s[100010];
int e[100010];
int ans[100010];

pll make_node(pll a, pll b)
{
	pll ret;

	ret.first.first = max(max(a.first.first, b.first.first), a.second.second + b.second.first);
	ret.first.second = a.first.second + b.first.second;
	ret.second.first = max(a.second.first, a.first.second + b.second.first);
	ret.second.second = max(b.second.second, b.first.second + a.second.second);

	return ret;
}

void update(int idx, int value)
{
	idx += len;
	tree[idx] = make_pair(make_pair(value, value), make_pair(value, value));
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = make_node(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

pll get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return make_pair(make_pair(-(1LL << 50), 0), make_pair(-(1LL << 50), -(1LL << 50)));
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return make_node(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int i;
	int a, b, c;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		v.push_back(make_pair(arr[i], i));
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b >> c;

		query.push_back(make_pair(make_pair(a, b), c));
	}

	for (i = 0; i < q; i++)
	{
		s[i] = 0;
		e[i] = 1000000000;
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

		for (i = 1; i <= n; i++) update(i, 1);

		idx = 0;
		for (i = 0; i < tv.size(); i++)
		{
			while (idx < v.size() && v[idx].first < tv[i].first)
			{
				update(v[idx].second, -100000);
				idx++;
			}

			if (get(1, 0, len - 1, query[tv[i].second].first.first, query[tv[i].second].first.second).first.first >= query[tv[i].second].second)
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
