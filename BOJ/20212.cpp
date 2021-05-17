#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
vector<pair<pair<pair<int, int>, pair<int, int>>, pair<int, int>>> v;
map<int, int> m;
int rm[SIZE];
long long tree[SIZE];
long long subtree[SIZE];
long long lazy[SIZE];
long long ans[50010];
bool is_print[50010];

bool comp(pair<pair<pair<int, int>, pair<int, int>>, pair<int, int>> a, pair<pair<pair<int, int>, pair<int, int>>, pair<int, int>> b)
{
	if (a.second.first != b.second.first) return a.second.first < b.second.first;
	else return a.first.first.first < b.first.first.first;
}

void propagate(int idx, int s, int e)
{
	int mid = (s + e) / 2;

	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += lazy[idx] * (rm[e] - rm[s] + 1);
	subtree[idx] += lazy[idx] * (rm[mid + 1] - rm[mid] - 1);
	lazy[idx] = 0;
}

void update(int idx, int s, int e, int v, int ts, int te)
{
	int mid;

	propagate(idx, s, e);
	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = v;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, v, ts, te);
	update(2 * idx + 1, mid + 1, e, v, ts, te);

	if (ts <= mid && te >= mid + 1) subtree[idx] += 1LL * v * (rm[mid + 1] - rm[mid] - 1);
	tree[idx] = tree[2 * idx] + tree[2 * idx + 1] + subtree[idx];
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te) + subtree[idx] * (ts <= mid && te >= mid + 1);
}

int main()
{
	int q;
	int i;
	int a, b, c, d;
	vector<int> tv;
	int idx;
	int cnt = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b >> c >> d;

		if (a == 1) idx = ++cnt;
		else idx = d;

		v.push_back(make_pair(make_pair(make_pair(a, b), make_pair(c, d)), make_pair(idx, i)));

		if (a == 2) is_print[i] = true;
	}

	for (i = 0; i < v.size(); i++)
	{
		tv.push_back(v[i].first.first.second);
		tv.push_back(v[i].first.second.first);
	}

	sort(tv.begin(), tv.end());

	idx = 0;
	for (i = 0; i < tv.size(); i++)
	{
		if (m.find(tv[i]) == m.end())
		{
			m[tv[i]] = idx;
			rm[idx] = tv[i];
			idx++;
		}
	}

	sort(v.begin(), v.end(), comp);

	for (i = 0; i < v.size(); i++)
	{
		if (v[i].first.first.first == 1)
		{
			update(1, 0, len - 1, v[i].first.second.second, m[v[i].first.first.second], m[v[i].first.second.first]);
		}
		else
		{
			ans[v[i].second.second] = get(1, 0, len - 1, m[v[i].first.first.second], m[v[i].first.second.first]);
		}
	}

	for (i = 0; i < q; i++)
	{
		if (is_print[i]) cout << ans[i] << '\n';
	}
}
