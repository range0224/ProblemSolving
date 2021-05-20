#include<iostream>
#include<vector>
#include<stack>
#include<map>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n, m;
int par[100010];
int depth[100010];
vector<pair<pair<int, int>, pair<int, int>>> v;
vector<pair<int, int>> query;
stack<pair<pair<int, int>, int>> st;
vector<int> tree[SIZE];
map<int, int> mp[100010];

void update(int idx, int s, int e, int ts, int te, int v)
{
	int mid;

	if (s > te || e < ts) return;
	
	tree[idx].push_back(v);

	if (ts <= s && e <= te) return;

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, v);
	update(2 * idx + 1, mid + 1, e, ts, te, v);
}

int find(int x)
{
	if (par[x] == x) return x;
	else return find(par[x]);
}

int union_(int x, int y)
{
	x = find(x);
	y = find(y);

	if (x == y) return 0;

	if (depth[x] > depth[y])
	{
		x ^= y;
		y ^= x;
		x ^= y;
	}

	par[x] = y;

	st.push(make_pair(make_pair(x, y), depth[x] == depth[y]));
	if (depth[x] == depth[y]) depth[y]++;

	return 1;
}

void rollback(int cnt)
{
	int a, b, c;

	while (cnt--)
	{
		a = st.top().first.first;
		b = st.top().first.second;
		c = st.top().second;
		st.pop();

		par[a] = a;
		depth[b] -= c;
	}
}

void recur(int idx, int s, int e)
{
	int mid;
	int i;
	int cnt = 0;

	if (s > e) return;
	if (s >= query.size()) return;

	for (i = 0; i < tree[idx].size(); i++)
	{
		if (v[tree[idx][i]].second.first > v[tree[idx][i]].second.second) continue;

		if (v[tree[idx][i]].second.first <= s && e <= v[tree[idx][i]].second.second)
		{
			cnt += union_(v[tree[idx][i]].first.first, v[tree[idx][i]].first.second);
		}
	}

	if (s == e)
	{
		if (find(query[s].first) == find(query[s].second)) cout << "1\n";
		else cout << "0\n";

		rollback(cnt);

		return;
	}

	mid = (s + e) / 2;

	recur(2 * idx, s, mid);
	recur(2 * idx + 1, mid + 1, e);

	rollback(cnt);
}

int main()
{
	int i;
	int a, b, c;
	int cnt = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		if (a == 1)
		{
			mp[min(b, c)][max(b, c)] = v.size();
			v.push_back(make_pair(make_pair(min(b, c), max(b, c)), make_pair(cnt, m)));
		}
		else if (a == 2)
		{
			v[mp[min(b, c)][max(b, c)]].second.second = cnt - 1;
		}
		else
		{
			query.push_back(make_pair(b, c));
			cnt++;
		}
	}

	for (i = 0; i < v.size(); i++)
	{
		if (v[i].second.second == m) v[i].second.second = cnt - 1;

		update(1, 0, len - 1, v[i].second.first, v[i].second.second, i);
	}

	for (i = 1; i <= n; i++) par[i] = i;

	recur(1, 0, len - 1);
}
