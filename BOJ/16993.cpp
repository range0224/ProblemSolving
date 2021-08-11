#include<iostream>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
pair<pair<int, int>, pair<int, int>> tree[SIZE];

pair<pair<int, int>, pair<int, int>> make_node(pair<pair<int, int>, pair<int, int>> l, pair<pair<int, int>, pair<int, int>> r)
{
	pair<pair<int, int>, pair<int, int>> ret;

	ret.first.first = max(max(l.first.first, r.first.first), l.second.second + r.second.first);
	ret.first.second = l.first.second + r.first.second;
	ret.second.first = max(l.second.first, l.first.second + r.second.first);
	ret.second.second = max(r.second.second, r.first.second + l.second.second);

	return ret;
}

void update(int idx, int value)
{
	idx += len;
	tree[idx].first.first = value;
	tree[idx].first.second = value;
	tree[idx].second.first = value;
	tree[idx].second.second = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = make_node(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

pair<pair<int, int>, pair<int, int>> get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return make_pair(make_pair(-100000000, 0), make_pair(-100000000, -100000000));
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return make_node(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		update(i, arr[i]);
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b;

		cout << get(1, 0, len - 1, a, b).first.first << '\n';
	}
}
