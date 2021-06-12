#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 20;
const int len = 1 << 19;
const int MAXV = 500010;
const long long MOD = 1LL << 32;
int n;
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV], out[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
unsigned long long tree[SIZE];
pair<unsigned long long, unsigned long long> lazy[SIZE];

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		lazy[2 * idx].first *= lazy[idx].first;
		lazy[2 * idx].first %= MOD;
		lazy[2 * idx].second *= lazy[idx].first;
		lazy[2 * idx].second %= MOD;
		lazy[2 * idx].second += lazy[idx].second;
		lazy[2 * idx].second %= MOD;

		lazy[2 * idx + 1].first *= lazy[idx].first;
		lazy[2 * idx + 1].first %= MOD;
		lazy[2 * idx + 1].second *= lazy[idx].first;
		lazy[2 * idx + 1].second %= MOD;
		lazy[2 * idx + 1].second += lazy[idx].second;
		lazy[2 * idx + 1].second %= MOD;
	}
	tree[idx] *= lazy[idx].first;
	tree[idx] %= MOD;
	tree[idx] += (e - s + 1) * lazy[idx].second;
	tree[idx] %= MOD;

	lazy[idx].first = 1;
	lazy[idx].second = 0;
}

void update(int idx, int s, int e, int ts, int te, int value, int option)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		if (option == 1) lazy[idx].second += value;
		else lazy[idx].first *= value;

		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value, option);
	update(2 * idx + 1, mid + 1, e, ts, te, value, option);

	tree[idx] = (tree[2 * idx] + tree[2 * idx + 1]) % MOD;
}

unsigned long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return (get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te)) % MOD;
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
	int q;
	int a, b, c, d;
	int i;
	unsigned long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 0; i < SIZE; i++) lazy[i].first = 1;

	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			update(1, 0, len - 1, in[b], out[b], c, 1);
		}
		else if (a == 2)
		{
			cin >> b >> c >> d;

			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				update(1, 0, len - 1, in[top[b]], in[b], d, 1);
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			update(1, 0, len - 1, in[b], in[c], d, 1);
		}
		else if (a == 3)
		{
			cin >> b >> c;

			update(1, 0, len - 1, in[b], out[b], c, 2);
		}
		else if (a == 4)
		{
			cin >> b >> c >> d;

			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				update(1, 0, len - 1, in[top[b]], in[b], d, 2);
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			update(1, 0, len - 1, in[b], in[c], d, 2);
		}
		else if (a == 5)
		{
			cin >> b;

			cout << get(1, 0, len - 1, in[b], out[b]) << '\n';
		}
		else
		{
			cin >> b >> c;

			ans = 0;
			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				ans += get(1, 0, len - 1, in[top[b]], in[b]);
				ans %= MOD;
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			ans += get(1, 0, len - 1, in[b], in[c]);
			ans %= MOD;

			cout << ans << '\n';
		}
	}
}
