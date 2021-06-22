#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
vector<int> v[MAXV];
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV], out[MAXV];
int cnt;
int tree[SIZE];
int lazy[SIZE];

void propagate(int idx, int s, int e)
{
	int i;

	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += lazy[idx];
	lazy[idx] = 0;
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

	tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
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
	out[cur] = cnt - 1;
}

int main()
{
	int q;
	int i;
	int a, b, c;
	bool option = true;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	cin >> a;
	for (i = 2; i <= n; i++)
	{
		cin >> a;

		v[a].push_back(i);
	}

	dfs1(1);
	dfs2(1);

	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			if (option) update(1, 0, len - 1, in[b], out[b], c);
			else
			{
				while (top[b] != top[1])
				{
					update(1, 0, len - 1, in[top[b]], in[b], c);
					b = par[top[b]];
				}
				update(1, 0, len - 1, in[1], in[b], c);
			}
		}
		else if (a == 2)
		{
			cin >> b;

			cout << get(1, 0, len - 1, in[b], in[b]) << '\n';
		}
		else option = !option;
	}
}
