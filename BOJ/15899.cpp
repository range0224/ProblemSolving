#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
const int SIZE = 1 << 19;
const int len = 1 << 18;
int n, c;
vector<pair<int, int>> color;
int in[200010], out[200010];
vector<int> input[200010];
vector<int> v[200010];
bool visited[200010];
int cnt;
int tree[SIZE];
vector<pair<int, int>> query;

void update(int idx)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx]++;
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

	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		dfs1(v[cur][i]);
	}
	out[cur] = cnt - 1;
}

int main()
{
	int i;
	int a, b;
	int q;
	int ans = 0;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q >> c;
	for (i = 1; i <= n; i++)
	{
		cin >> a;

		color.push_back(make_pair(a, i));
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		input[a].push_back(b);
		input[b].push_back(a);
	}
	while (q--)
	{
		cin >> a >> b;

		query.push_back(make_pair(b, a));
	}

	dfs(1);
	dfs1(1);

	sort(color.begin(), color.end());
	sort(query.begin(), query.end());

	idx = 0;
	for (i = 0; i < query.size(); i++)
	{
		while (idx < color.size() && color[idx].first <= query[i].first) update(in[color[idx++].second]);

		ans += get(1, 0, len - 1, in[query[i].second], out[query[i].second]);
		ans %= MOD;
	}

	cout << ans;
}
