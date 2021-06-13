#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int arr[MAXV];
int sz[MAXV], par[MAXV], depth[MAXV], top[MAXV], in[MAXV], out[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
long long tree[SIZE];
int cnt;

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = tree[2 * idx] ^ tree[2 * idx + 1];
		idx /= 2;
	}
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) ^ get(2 * idx + 1, mid + 1, e, ts, te);
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
	int i;
	int a, b, c;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
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

	for (i = 1; i <= n; i++)
	{
		update(in[i], arr[i]);
	}

	while (q--)
	{
		cin >> a >> b >> c;

		if (a == 1) update(in[b], c);
		else
		{
			ans = 0;
			while (top[b] != top[c])
			{
				if (depth[top[b]] < depth[top[c]]) swap(b, c);

				ans ^= get(1, 0, len - 1, in[top[b]], in[b]);
				b = par[top[b]];
			}
			if (depth[b] > depth[c]) swap(b, c);

			ans ^= get(1, 0, len - 1, in[b], in[c]);

			cout << ans << '\n';
		}
	}
}
