#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

typedef struct node_t
{
	long long mx, mn;
	long long sum;
}node;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
node tree[SIZE];
long long lazy1[SIZE];
long long lazy2[SIZE];

node merge(node a, node b)
{
	node ret;

	ret.mn = min(a.mn, b.mn);
	ret.mx = max(a.mx, b.mx);
	ret.sum = a.sum + b.sum;

	return ret;
}

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		if (lazy1[idx])
		{
			lazy1[2 * idx] = lazy1[idx];
			lazy1[2 * idx + 1] = lazy1[idx];
			lazy2[2 * idx] = 0;
			lazy2[2 * idx + 1] = 0;
		}
		lazy2[2 * idx] += lazy2[idx];
		lazy2[2 * idx + 1] += lazy2[idx];
	}
	if (lazy1[idx])
	{
		tree[idx].mn = lazy1[idx];
		tree[idx].mx = lazy1[idx];
		tree[idx].sum = lazy1[idx] * (e - s + 1);
	}
	tree[idx].mn += lazy2[idx];
	tree[idx].mx += lazy2[idx];
	tree[idx].sum += lazy2[idx] * (e - s + 1);

	lazy1[idx] = 0;
	lazy2[idx] = 0;
}

void update_sqrt(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		if (floor(sqrt(tree[idx].mn)) == floor(sqrt(tree[idx].mx)))
		{
			lazy1[idx] = floor(sqrt(tree[idx].mn));
			propagate(idx, s, e);
			return;
		}
		else if (tree[idx].mn + 1 == tree[idx].mx)
		{
			lazy2[idx] = floor(sqrt(tree[idx].mn)) - tree[idx].mn;
			propagate(idx, s, e);
			return;
		}
	}

	mid = (s + e) / 2;

	update_sqrt(2 * idx, s, mid, ts, te);
	update_sqrt(2 * idx + 1, mid + 1, e, ts, te);

	tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy2[idx] = value;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);

	tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx].sum;

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i;
	int a, b, c, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	for (i = 0; i < SIZE; i++)
	{
		tree[i].mn = 0;
		tree[i].mx = 0;
		tree[i].sum = 0;
	}

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> a;

		tree[i + len].mn = a;
		tree[i + len].mx = a;
		tree[i + len].sum = a;
	}

	for (i = len - 1; i >= 1; i--)
	{
		tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
	}

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

			update_sqrt(1, 0, len - 1, b, c);
		}
		else
		{
			cin >> b >> c;

			cout << get(1, 0, len - 1, b, c) << '\n';
		}
	}
}
