#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct node_t
{
    node_t* l;
    node_t* r;
    node_t* p;
    int key, cnt;
    long long v;
    long long sum;
    bool flip;
}node;

int n;
node* tree;
node* ptr[100010];

void push(node* x)
{
    if (!x->flip) return;

    swap(x->l, x->r);

    if (x->l) x->l->flip = !x->l->flip;
    if (x->r) x->r->flip = !x->r->flip;

    x->flip = false;
}

void update(node* x)
{
    push(x);
    x->sum = x->v;
    x->cnt = 1;

    if (x->l) {
        push(x->l);
        x->cnt += x->l->cnt;
        x->sum += x->l->sum;
    }
    if (x->r) {
        push(x->r);
        x->cnt += x->r->cnt;
        x->sum += x->r->sum;
    }
}

void rotate(node* x)
{
    node* p = x->p;
    node* b = NULL;

    if (!p) return;

    push(p);
    push(x);
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

void splay(node* x, node* g = NULL)
{
    node* p;

    while (x->p != g)
    {
        p = x->p;
        if (p->p == g)
        {
            rotate(x);
            break;
        }

        if ((x == p->l) == (p == p->p->l)) rotate(p);
        else rotate(x);

        rotate(x);
    }
    if (!g) tree = x;
}

void insert(int key, int value)
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
        tree->flip = false;
        return;
    }

    while (1)
    {
        push(p);

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
    x->flip = false;

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

    push(tree);
    push(tree->r);
    push(tree->r->l);

    return tree->r->l;
}

void flip(int s, int e)
{
    node* x = gather(s, e);
    x->flip = !x->flip;
}

void inorder(node* x)
{
    push(x);

    if (x->l) inorder(x->l);
    cout << x->v << ' ';
    if (x->r) inorder(x->r);
}

int get_idx(node* x)
{
    splay(x);

    return tree->l->cnt;
}

int main()
{
    int q;
    int i;
    int a, b;
    node* x;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n >> q;

    insert(0, 0);
    for (i = 1; i <= n; i++)
    {
        insert(i, i);

        ptr[i] = tree;
    }
    insert(n + 1, 0);

    while (q--)
    {
        cin >> a >> b;

        a = get_idx(ptr[a]);
        b = get_idx(ptr[b]);

        if (a == b + 1)
        {
            cout << 0 << '\n';
        }
        else if (a < b)
        {
            cout << b - a << '\n';

            flip(a + 1, b);
            flip(a, b);
        }
        else
        {
            cout << b - a + 1 << '\n';

            flip(b + 1, a - 1);
            flip(b + 1, a);
        }
    }

    inorder(gather(1, n));
}
