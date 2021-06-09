#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV], out[MAXV];
int cnt;
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int to_node[MAXV];
int tree[SIZE];
int color[MAXV];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
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

int get_first(int idx, int s, int e, int ts, int te)
{
	int mid;
	int ret;

	if (s > te || e < ts) return -1;
	else if (!tree[idx]) return -1;
	else if (s == e) return to_node[s];

	mid = (s + e) / 2;

	ret = get_first(2 * idx, s, mid, ts, te);

	if (ret != -1) return ret;
	else return get_first(2 * idx + 1, mid + 1, e, ts, te);
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

	in[cur] = cnt;
	to_node[cnt++] = cur;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (i == 0) top[v[cur][i]] = top[cur];
		else top[v[cur][i]] = v[cur][i];

		dfs2(v[cur][i]);
	}
	out[cur] = cnt;
}

int main()
{
	int i;
	int a, b;
	int q;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	cin >> q;
	while (q--)
	{
		cin >> a >> b;

		if (a == 1)
		{
			color[b] = !color[b];

			update(in[b], color[b]);
		}
		else
		{
			ans = -1;
			while (b)
			{
				if (get(1, 0, len - 1, in[top[b]], in[b])) ans = get_first(1, 0, len - 1, in[top[b]], in[b]);
				b = par[top[b]];
			}
			cout << ans << '\n';
		}
	}
}
