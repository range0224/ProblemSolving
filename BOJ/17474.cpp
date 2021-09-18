#include<iostream>
#include<algorithm>
using namespace std;

typedef struct node_t
{
	int mx;
	int mx2;
	int cnt;
	long long sum;
}node;

const int INF = (1LL << 31) - 1;
const int SIZE = 1 << 21;
const int len = 1 << 20;
int n;
int arr[1000010];
node tree[SIZE];
int lazy[SIZE];

node merge(node a, node b)
{
	node ret;

	if (a.mx > b.mx)
	{
		ret.mx = a.mx;
		ret.mx2 = max(a.mx2, b.mx);
		ret.cnt = a.cnt;
	}
	else if (a.mx < b.mx)
	{
		ret.mx = b.mx;
		ret.mx2 = max(a.mx, b.mx2);
		ret.cnt = b.cnt;
	}
	else
	{
		ret.mx = a.mx;
		ret.mx2 = max(a.mx2, b.mx2);
		ret.cnt = a.cnt + b.cnt;
	}
	ret.sum = a.sum + b.sum;

	return ret;
}

void propagate(int idx, int s, int e)
{
	if (tree[idx].mx <= lazy[idx]) return;

	if (idx < len)
	{
		lazy[2 * idx] = min(lazy[2 * idx], lazy[idx]);
		lazy[2 * idx + 1] = min(lazy[2 * idx + 1], lazy[idx]);
	}
	tree[idx].sum -= (0LL + tree[idx].mx - lazy[idx]) * tree[idx].cnt;
	tree[idx].mx = lazy[idx];
	lazy[idx] = INF;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts || tree[idx].mx <= value) return;
	else if (ts <= s && e <= te && tree[idx].mx2 < value)
	{
		lazy[idx] = value;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);
	
	tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

int get_max(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return -1;
	else if (ts <= s && e <= te) return tree[idx].mx;

	mid = (s + e) / 2;

	return max(get_max(2 * idx, s, mid, ts, te), get_max(2 * idx + 1, mid + 1, e, ts, te));
}

long long get_sum(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx].sum;

	mid = (s + e) / 2;

	return get_sum(2 * idx, s, mid, ts, te) + get_sum(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i;
	int a, b, c, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	for (i = len; i < SIZE; i++)
	{
		tree[i].mx = 0;
		tree[i].mx2 = -1;
		tree[i].sum = 0;
		tree[i].cnt = 0;
	}

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		tree[i + len].mx = arr[i];
		tree[i + len].mx2 = -1;
		tree[i + len].sum = arr[i];
		tree[i + len].cnt = 1;
	}

	for (i = len - 1; i >= 1; i--)
	{
		tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
	}

	for (i = 0; i < SIZE; i++) lazy[i] = INF;

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c >> d;

			update(1, 0, len - 1, b, c, d);
		}
		else if (a == 2)
		{
			cin >> b >> c;

			cout << get_max(1, 0, len - 1, b, c) << '\n';
		}
		else if (a == 3)
		{
			cin >> b >> c;

			cout << get_sum(1, 0, len - 1, b, c) << '\n';
		}
	}
}
