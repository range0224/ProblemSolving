#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<pair<int, int>, pair<int, int>> pii;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int arr[MAXV];
vector<int> v[MAXV];
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
bool visited[MAXV];
int cnt;
pii tree[SIZE];
int lazy[SIZE];

pii make_node(pii a, pii b)
{
	pii ret;

	ret.first.first = max(max(a.first.first, b.first.first), a.second.second + b.second.first);
	ret.first.second = a.first.second + b.first.second;
	ret.second.first = max(a.second.first, a.first.second + b.second.first);
	ret.second.second = max(b.second.second, b.first.second + a.second.second);

	return ret;
}

void make_tree()
{
	int i;

	for (i = len - 1; i >= 1; i--)
	{
		tree[i] = make_node(tree[2 * i], tree[2 * i + 1]);
	}
}

void propagate(int idx, int s, int e)
{
	if (lazy[idx] == -100000) return;

	if (idx < len)
	{
		lazy[2 * idx] = lazy[idx];
		lazy[2 * idx + 1] = lazy[idx];
	}
	tree[idx] = make_pair(make_pair(max(0, lazy[idx] * (e - s + 1)), lazy[idx] * (e - s + 1)), make_pair(max(0, lazy[idx] * (e - s + 1)), max(0, lazy[idx] * (e - s + 1))));
	lazy[idx] = -100000;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = value;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);

	tree[idx] = make_node(tree[2 * idx], tree[2 * idx + 1]);
}

pii get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return make_pair(make_pair(0, 0), make_pair(0, 0));
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return make_node(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	for (i = 0; i < input[cur].size(); i++)
	{
		if (visited[input[cur][i]]) continue;

		v[cur].push_back(input[cur][i]);
		dfs(input[cur][i]);
	}
}

void dfs1(int cur)
{
	int i;

	sz[cur] = 1;
	for (i = 0; i < v[cur].size(); i++)
	{
		depth[v[cur][i]] = depth[cur] + 1;
		par[v[cur][i]] = cur;
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
}

int main()
{
	int q;
	int i;
	int a, b, c, d;
	pii ans1, ans2;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 0; i < SIZE; i++) lazy[i] = -100000;

	for (i = 1; i <= n; i++)
	{
		tree[in[i] + len] = make_pair(make_pair(max(0, arr[i]), arr[i]), make_pair(max(0, arr[i]), max(0, arr[i])));
	}

	make_tree();

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			ans1 = make_pair(make_pair(0, 0), make_pair(0, 0));
			ans2 = make_pair(make_pair(0, 0), make_pair(0, 0));
			while (top[b] != top[c])
			{
				if (depth[top[b]] > depth[top[c]])
				{
					ans1 = make_node(get(1, 0, len - 1, in[top[b]], in[b]), ans1);
					b = par[top[b]];
				}
				else
				{
					ans2 = make_node(get(1, 0, len - 1, in[top[c]], in[c]), ans2);
					c = par[top[c]];
				}
			}

			if (depth[b] < depth[c])
			{
				ans2 = make_node(get(1, 0, len - 1, in[b], in[c]), ans2);
			}
			else
			{
				ans1 = make_node(get(1, 0, len - 1, in[c], in[b]), ans1);
			}

			cout << max(max(ans1.first.first, ans2.first.first), ans1.second.first + ans2.second.first) << '\n';
		}
		else
		{
			cin >> b >> c >> d;

			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				update(1, 0, len - 1, in[top[b]], in[b], d);
				b = par[top[b]];
			}

			if (depth[b] > depth[c]) swap(b, c);

			update(1, 0, len - 1, in[b], in[c], d);
		}
	}
}
