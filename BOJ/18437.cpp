#include<iostream>
#include<vector>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
vector<int> v[100010];
int in[100010];
int out[100010];
int tree[SIZE];
int lazy[SIZE];
int cnt;

void propagate(int idx, int s, int e)
{
    if (idx < len && lazy[idx])
    {
        lazy[2 * idx] = lazy[idx];
        lazy[2 * idx + 1] = lazy[idx];
    }

    if (lazy[idx] == 1) tree[idx] = (e - s + 1);
    else if (lazy[idx] == 2) tree[idx] = 0;

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

int get(int idx, int s, int e, int ts, int te)
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
    int a, b;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    for (i = 1; i <= n; i++)
    {
        cin >> a;
        v[a].push_back(i);
    }

    dfs(1);

    update(1, 0, len - 1, in[1], out[1], 1);

    cin >> q;
    while (q--)
    {
        cin >> a >> b;

        if (a <= 2) update(1, 0, len - 1, in[b] + 1, out[b], a);
        else cout << get(1, 0, len - 1, in[b] + 1, out[b]) << '\n';
    }
}
