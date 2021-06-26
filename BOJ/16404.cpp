#include<iostream>
#include<vector>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
vector<int> v[MAXV];
int in[MAXV], out[MAXV];
long long tree[SIZE];
long long lazy[SIZE];
int cnt;

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += (e - s + 1) * lazy[idx];
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

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

void dfs(int cur)
{
	int i;

	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		dfs(v[cur][i]);
	}
	out[cur] = cnt - 1;
}

int main()
{
	int q;
	int i;
	int a, b, c;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	cin >> a;
	for (i = 2; i <= n; i++)
	{
		cin >> a;

		v[a].push_back(i);
	}

	dfs(1);

	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			update(1, 0, len - 1, in[b], out[b], c);
		}
		else
		{
			cin >> b;

			cout << get(1, 0, len - 1, in[b], in[b]) << '\n';
		}
	}
}
