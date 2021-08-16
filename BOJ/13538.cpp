#include<iostream>
using namespace std;

typedef struct node_t
{
	int value;
	node_t* l;
	node_t* r;
}node;

const int len = 1 << 19;
int n;
node tree[500010];

void make_tree(node& r, int s, int e)
{
	int mid;

	if (s == e)
	{
		r.value = 0;
		return;
	}

	mid = (s + e) / 2;

	r.l = new node();
	r.r = new node();
	make_tree(*r.l, s, mid);
	make_tree(*r.r, mid + 1, e);
	r.value = r.l->value + r.r->value;
}

void update(node& prv, node& root, int s, int e, int idx)
{
	int mid;

	if (s == e)
	{
		root.value++;
		return;
	}

	mid = (s + e) / 2;

	if (idx <= mid)
	{
		root.l = new node();
		root.r = prv.r;
		root.l->value = prv.l->value;
		update(*prv.l, *root.l, s, mid, idx);
	}
	else
	{
		root.l = prv.l;
		root.r = new node();
		root.r->value = prv.r->value;
		update(*prv.r, *root.r, mid + 1, e, idx);
	}

	root.value = root.l->value + root.r->value;
}

int get_xor(node& prv, node& root, int s, int e, int value, int bit)
{
	int mid;

	if (s == e) return s;

	mid = (s + e) / 2;

	if (value & bit)
	{
		if (root.l->value - prv.l->value) return get_xor(*prv.l, *root.l, s, mid, value, bit / 2);
		else return get_xor(*prv.r, *root.r, mid + 1, e, value, bit / 2);
	}
	else
	{
		if (root.r->value - prv.r->value) return get_xor(*prv.r, *root.r, mid + 1, e, value, bit / 2);
		else return get_xor(*prv.l, *root.l, s, mid, value, bit / 2);
	}
}

int get_kth(node& prv, node& root, int s, int e, int k)
{
	int mid;

	if (s == e) return s;

	mid = (s + e) / 2;

	if (root.l->value - prv.l->value >= k) return get_kth(*prv.l, *root.l, s, mid, k);
	else
	{
		k -= root.l->value - prv.l->value;
		return get_kth(*prv.r, *root.r, mid + 1, e, k);
	}
}

int get(node& prv, node& root, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return root.value - prv.value;

	mid = (s + e) / 2;

	return get(*prv.l, *root.l, s, mid, ts, te) + get(*prv.r, *root.r, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int a, b, c, d;

	n = 1;
	make_tree(tree[0], 0, len - 1);

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b;

			update(tree[n - 1], tree[n], 0, len - 1, b);
			n++;
		}
		else if (a == 2)
		{
			cin >> b >> c >> d;

			cout << get_xor(tree[b - 1], tree[c], 0, len - 1, d, len / 2) << '\n';
		}
		else if (a == 3)
		{
			cin >> b;

			n -= b;
		}
		else if (a == 4)
		{
			cin >> b >> c >> d;

			cout << get(tree[b - 1], tree[c], 0, len - 1, 0, d) << '\n';
		}
		else
		{
			cin >> b >> c >> d;

			cout << get_kth(tree[b - 1], tree[c], 0, len - 1, d) << '\n';
		}
	}
}
