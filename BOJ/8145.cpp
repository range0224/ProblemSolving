#include<iostream>
#include<vector>
using namespace std;

const int SIZE = 1 << 19;
const int len = 1 << 18;
const int MAXV = 250010;
int n;
int sz[MAXV], depth[MAXV], par[MAXV], top[MAXV], in[MAXV];
vector<int> input[MAXV];
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
int tree[SIZE];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while(idx >= 1)
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
	char a;
	int b, c;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n - 1; i++)
	{
		cin >> b >> c;

		input[b].push_back(c);
		input[c].push_back(b);
	}

	dfs(1);
	dfs1(1);
	dfs2(1);

	for (i = 2; i <= n; i++)
	{
		update(in[i], 1);
	}

	cin >> q;
	while (q)
	{
		cin.ignore();
		cin >> a;

		if (a == 'W')
		{
			cin >> b;

			ans = 0;
			while (top[b] != top[1])
			{
				ans += get(1, 0, len - 1, in[top[b]], in[b]);
				b = par[top[b]];
			}
			ans += get(1, 0, len - 1, in[1], in[b]);

			cout << ans << '\n';

			q--;
		}
		else
		{
			cin >> b >> c;

			if (par[b] == c) update(in[b], 0);
			else update(in[c], 0);
		}
	}
}
