#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 21;
const int len = 1 << 20;
const int MAXV = 1000010;
int n;
vector<int> v[MAXV];
int in[MAXV], out[MAXV];
int cnt;
int mn_tree[SIZE];
int mx_tree[SIZE];
int lazy[SIZE];

void init()
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        mn_tree[i] = 0;
        mx_tree[i] = 0;
        lazy[i] = 0;
    }
}

void propagate(int idx, int s, int e)
{
    if (idx < len)
    {
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
    }

    mx_tree[idx] += lazy[idx];
    mn_tree[idx] += lazy[idx];
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

    mx_tree[idx] = max(mx_tree[2 * idx], mx_tree[2 * idx + 1]);
    mn_tree[idx] = min(mn_tree[2 * idx], mn_tree[2 * idx + 1]);
}
pair<int, int> get(int idx, int s, int e, int ts, int te)
{
    pair<int, int> a, b;
    int mid;

    propagate(idx, s, e);

    if (s > te || e < ts) return make_pair(1000000000, -1000000000);
    else if (ts <= s && e <= te) return make_pair(mn_tree[idx], mx_tree[idx]);

    mid = (s + e) / 2;

    a = get(2 * idx, s, mid, ts, te);
    b = get(2 * idx + 1, mid + 1, e, ts, te);

    return make_pair(min(a.first, b.first), max(a.second, b.second));
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
    int t;
    int i;
    char a;
    int b, c;
    int q;
    pair<int, int> temp;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> t;
    while (t--)
    {
        init();

        cin >> n;

        for (i = 1; i <= n; i++) v[i].clear();
        for (i = 2; i <= n; i++)
        {
            cin >> b;
            v[b].push_back(i);
        }

        cnt = 0;
        dfs(1);

        for (i = 1; i <= n; i++)
        {
            cin >> b;

            update(1, 0, len - 1, in[i], in[i], b);
        }

        cin >> q;
        while (q--)
        {
            cin.ignore();

            cin >> a;

            if (a == 'Q')
            {
                cin >> b;

                temp = get(1, 0, len - 1, in[b], out[b]);
                cout << temp.second - temp.first << '\n';
            }
            else
            {
                cin >> b >> c;

                update(1, 0, len - 1, in[b], out[b], c);
            }
        }
    }
}
