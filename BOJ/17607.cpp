#include<iostream>
#include<algorithm>
using namespace std;

typedef struct node_t
{
	node_t* l;
	node_t* r;
	node_t* p;
	int key, cnt;
	long long v;
	long long sum, lazy;
	long long lsum, rsum, mx;
	bool flip;
}node;

node* tree;

void push(node *x)
{
	x->v += x->lazy;
	if (x->l)
	{
		x->l->lazy += x->lazy;
		x->l->sum += x->l->cnt * x->lazy;
	}
	if (x->r)
	{
		x->r->lazy += x->lazy;
		x->r->sum += x->r->cnt * x->lazy;
	}
	x->lazy = 0;

	if (!x->flip) return;

	swap(x->l, x->r);
	swap(x->lsum, x->rsum);

	if (x->l) x->l->flip = !x->l->flip;
	if (x->r) x->r->flip = !x->r->flip;

	x->flip = false;
}

void update(node* x)
{
	x->sum = x->v;
	x->cnt = 1;
	x->lsum = x->v;
	x->rsum = x->v;
	x->mx = x->v;
	
	if (x->l && x->r) {
		push(x->l);
		push(x->r);
		x->cnt += x->l->cnt + x->r->cnt;
		x->lsum = x->l->lsum + (x->l->cnt == x->l->lsum && x->v ? 1 + x->r->lsum : 0);
		x->rsum = x->r->rsum + (x->r->cnt == x->r->rsum && x->v ? x->l->rsum + 1 : 0);
		x->mx = max({ x->l->mx, x->r->mx, x->v ? x->l->rsum + 1 + x->r->lsum : 0 });
	}
	else if (x->l) {
		push(x->l);
		x->cnt += x->l->cnt;
		x->lsum = x->l->lsum + (x->l->cnt == x->l->lsum ? x->v : 0);
		x->rsum = x->v ? x->l->rsum + 1 : 0;
		x->mx = max(x->l->mx, x->v ? x->l->rsum + 1 : 0);
	}
	else if (x->r) {
		push(x->r);
		x->cnt += x->r->cnt;
		x->lsum = x->v ? 1 + x->r->lsum : 0;
		x->rsum = x->r->rsum + (x->r->cnt == x->r->rsum ? x->v : 0);
		x->mx = max(x->r->mx, x->v ? x->r->lsum + 1 : 0);
	}
}

void rotate(node *x)
{
	node* p = x->p;
	node* b = NULL;

	if (!p) return;

	if (x == p->l)
	{
		p->l = b = x->r;
		x->r = p;
	}
	else
	{
		p->r = b = x->l;
		x->l = p;
	}

	x->p = p->p;
	p->p = x;
	if (b) b->p = p;

	if (x->p)
	{
		if (x->p->l == p) x->p->l = x;
		else x->p->r = x;
	}
	else tree = x;

	update(p);
	update(x);
}

void splay(node *x, node *g = NULL)
{
	node* y;
	node* p;

	while (x->p != g)
	{
		p = x->p;
		if (p->p == g)
		{
			rotate(x);
			return;
		}

		if ((x == p->l) == (p == p->p->l)) rotate(p);
		else rotate(x);

		rotate(x);
	}
	if (!g) tree = x;
}

void insert(int key, long long value)
{
	node* p = tree;
	node** pp;
	node* x;

	if (!p)
	{
		tree = new node;
		tree->l = tree->r = tree->p = NULL;
		tree->key = key;
		tree->v = value;
		tree->lazy = 0;
		tree->flip = false;
		tree->lsum = tree->rsum = tree->mx = 0;
		return;
	}

	while (1)
	{
		if (key == p->key) return;

		if (key < p->key)
		{
			if (!p->l)
			{
				pp = &p->l;
				break;
			}
			p = p->l;
		}
		else
		{
			if (!p->r)
			{
				pp = &p->r;
				break;
			}
			p = p->r;
		}
	}
	x = new node;
	*pp = x;
	x->l = x->r = NULL;
	x->p = p;
	x->key = key;
	x->v = value;
	x->lazy = 0;
	x->flip = false;
	tree->lsum = tree->rsum = tree->mx = 0;

	splay(x);
}

bool find(int key)
{
	node* p = tree;
	
	if (!p) return false;

	while (p)
	{
		if (key == p->key) break;

		if (key < p->key)
		{
			if (!p->l) break;
			p = p->l;
		}
		else
		{
			if (!p->r) break;
			p = p->r;
		}
	}

	splay(p);
	return key == p->key;
}

void delete_(int key)
{
	node* p;
	node* x;

	if (!find(key)) return;

	p = tree;
	if (p->l && p->r)
	{
		tree = p->l;
		tree->p = NULL;

		x = tree;
		while (x->r) x = x->r;
		x->r = p->r;
		p->r->p = x;
		delete p;
		return;
	}
	else if (p->l)
	{
		tree = p->l;
		tree->p = NULL;
		delete p;
	}
	else if (p->r)
	{
		tree = p->r;
		tree->p = NULL;
		delete p;
	}
	else
	{
		delete p;
		tree = NULL;
	}
}

void kth(int k)
{
	node* x = tree;
	push(x);
	while (1)
	{
		while (x->l && x->l->cnt > k)
		{
			x = x->l;
			push(x);
		}
		if (x->l) k -= x->l->cnt;
		if (!k--) break;
		x = x->r;
		push(x);
	}
	splay(x);
}

node* gather(int s, int e)
{
	node* temp;

	kth(e + 1);
	temp = tree;
	kth(s - 1);
	splay(temp, tree);

	return tree->r->l;
}

void flip(int s, int e)
{
	node* x = gather(s, e);
	x->flip = !x->flip;
}

int n;

int main()
{
	int q;
	int i;
	int a, b, c;
	node* x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	insert(0, 0);
	for (i = 1; i <= n; i++)
	{
		cin >> a;

		insert(i, a);
	}
	insert(n + 1, 0);

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c;

		if (a == 1)
		{
			flip(b, c);
			
			update(tree);
		}
		else
		{
			x = gather(b, c);

			cout << x->mx << '\n';
		}
	}
}
