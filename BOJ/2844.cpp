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
    long long set;
    long long add, gap;
    bool flip;
}node;

int n;
node* tree;

void push(node* x)
{
    int cnt;

    if (x->set != -1)
    {
        x->v = x->set;
        x->sum = x->set * x->cnt;

        if (x->l)
        {
            x->l->set = x->set;
            x->l->add = 0;
            x->l->gap = 0;
        }
        if (x->r)
        {
            x->r->set = x->set;
            x->r->add = 0;
            x->r->gap = 0;
        }

        x->set = -1;
    }

    cnt = 1;
    if (x->l) cnt = x->l->cnt + 1;

    x->v += x->add + (cnt - 1) * x->gap;
    x->sum += (x->add + x->add + (x->cnt - 1) * x->gap) * x->cnt / 2;

    if (x->l)
    {
        x->l->add += x->add;
        x->l->gap += x->gap;
    }
    if (x->r)
    {
        x->r->add += x->add + cnt * x->gap;
        x->r->gap += x->gap;
    }
    x->add = 0;
    x->gap = 0;

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
    vector<int> v;
    int i;

    if (g != NULL) push(g);

    p = x;
    while (p->p != g)
    {
        if (p->p->l == p) v.push_back(0);
        else v.push_back(1);

        p = p->p;
    }

    for (i = v.size() - 1; i >= 0; i--)
    {
        push(p);

        if (v[i] == 0) p = p->l;
        else p = p->r;
    }
    push(p);

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
        tree->add = 0;
        tree->gap = 0;
        tree->set = -1;
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
    x->add = 0;
    x->gap = 0;
    x->set = -1;
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

int get_idx(node* x)
{
    splay(x);

    return tree->l->cnt;
}

void inorder(node* x)
{
    push(x);

    if (x->l) inorder(x->l);
    cout << x->v << ' ';
    if (x->r) inorder(x->r);
}

int main()
{
    int q;
    int i;
    int a, b, c, d;
    int cnt;
    node* x;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n >> q;

    insert(0, 0);
    for (i = 1; i <= n; i++)
    {
        cin >> a;

        insert(i, a);
    }
    insert(300000, 0);

    cnt = n;

    while (q--)
    {
        cin >> a;

        if (a == 1)
        {
            cin >> b >> c >> d;

            x = gather(b, c);

            push(x);

            x->set = d;
            x->add = 0;
            x->gap = 0;

            push(x);
        }
        else if (a == 2)
        {
            cin >> b >> c >> d;

            x = gather(b, c);

            x->add = d;
            x->gap = d;

            push(x);
        }
        else if (a == 3)
        {
            cin >> b >> c;

            insert(++cnt, c);

            if (b == cnt) continue;

            flip(b, cnt - 1);
            flip(b, cnt);
        }
        else
        {
            cin >> b >> c;

            cout << gather(b, c)->sum << '\n';
        }
    }
}
