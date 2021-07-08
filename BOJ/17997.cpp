#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MOD = 11092019;
const int SIZE = 1 << 21;
const int len = 1 << 20;
const int MAXV = 1000010;
int n;
int arr[MAXV];
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV], out[MAXV];
vector<int> v[MAXV];
int cnt;
vector<pair<pair<int, int>, int>> tv;
pair<int, int> tree[SIZE];

void update(int idx, pair<int, int> value)
{
	idx += len;
	while (idx >= 1)
	{
		if (tree[idx].first < value.first) tree[idx] = value;
		else if (tree[idx].first == value.first) tree[idx].second = (tree[idx].second + value.second) % MOD;

		idx /= 2;
	}
}

pair<int, int> get(int idx, int s, int e, int ts, int te)
{
	int mid;
	pair<int, int> a, b;

	if (s > te || e < ts) return make_pair(0, 0);
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	a = get(2 * idx, s, mid, ts, te);
	b = get(2 * idx + 1, mid + 1, e, ts, te);

	if (a.first > b.first) return a;
	else if (a.first < b.first) return b;
	else return make_pair(a.first, (a.second + b.second) % MOD);
}

void dfs1(int cur)
{
	int i;

	sz[cur] = 1;
	for (i = 0; i < v[cur].size(); i++)
	{
		par[v[cur][i]] = cur;
		depth[v[cur][i]] = depth[cur] + 1;
		dfs1(v[cur][i]);
		sz[cur] += sz[v[cur][i]];

		if (sz[v[cur][i]] > sz[v[cur][0]]) swap(v[cur][i], v[cur][0]);
	}
}

void dfs2(int cur)
{
	int i;

	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (i == 0) top[v[cur][i]] = top[cur];
		else top[v[cur][i]] = v[cur][i];

		dfs2(v[cur][i]);
	}
	out[cur] = cnt - 1;
}

int main()
{
	int i;
	int x;
	int cur;
	pair<int, int> p;
	pair<int, int> ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 2; i <= n; i++)
	{
		cin >> x;

		v[x].push_back(i);
	}

	dfs1(1);
	dfs2(1);

	for (i = 1; i <= n; i++)
	{
		tv.push_back(make_pair(make_pair(arr[i], depth[i]), i));
	}

	sort(tv.begin(), tv.end());

	for (i = 0; i < tv.size(); i++)
	{
		cur = tv[i].second;

		update(in[cur], make_pair(0, 1));

		while (top[cur] != top[1])
		{
			p = get(1, 0, len - 1, in[top[cur]], in[cur]);

			update(in[tv[i].second], make_pair(p.first + 1, p.second));
			cur = par[top[cur]];
		}
		p = get(1, 0, len - 1, in[1], in[cur]);

		update(in[tv[i].second], make_pair(p.first + 1, p.second));
	}

	ans = get(1, 0, len - 1, in[1], out[1]);

	cout << ans.first << ' ' << ans.second;
}
