#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef struct node_t
{
	int value;
	int l, r;
}node;

const int len = 1 << 20;
int n;
int arr[1000010];
node tree[50000010];
int root[2000010];
int prv[1000010];
vector<pair<int, int>> tv;
int cnt;

void make_tree(node& root, int s, int e)
{
	int mid;

	root.value = 0;

	if (s == e) return;

	mid = (s + e) / 2;

	root.l = cnt++;
	root.r = cnt++;
	make_tree(tree[root.l], s, mid);
	make_tree(tree[root.r], mid + 1, e);
}

void update(node& prv, node& root, int s, int e, int idx, int value)
{
	int mid;

	if (s == e)
	{
		root.value = value;
		return;
	}

	mid = (s + e) / 2;

	if (idx <= mid)
	{
		root.l = cnt++;
		root.r = prv.r;
		update(tree[prv.l], tree[root.l], s, mid, idx, value);
	}
	else
	{
		root.l = prv.l;
		root.r = cnt++;
		update(tree[prv.r], tree[root.r], mid + 1, e, idx, value);
	}

	root.value = tree[root.l].value + tree[root.r].value;
}

int get(node& root, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return root.value;

	mid = (s + e) / 2;

	return get(tree[root.l], s, mid, ts, te) + get(tree[root.r], mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i;
	int a, b;
	int ans = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	for (i = 1; i <= n; i++) tv.push_back(make_pair(arr[i], i));

	sort(tv.begin(), tv.end());

	a = 1;
	b = 0;
	for (i = 0; i < tv.size(); i++)
	{
		if (tv[i].first != tv[b].first)
		{
			a++;
			b = i;
		}

		arr[tv[i].second] = a;
	}

	root[0] = cnt++;
	make_tree(tree[0], 0, len - 1);

	for (i = 1; i <= n; i++)
	{
		root[2 * i - 1] = cnt++;
		update(tree[root[2 * i - 2]], tree[root[2 * i - 1]], 0, len - 1, i, 1);
		root[2 * i] = cnt++;
		update(tree[root[2 * i - 1]], tree[root[2 * i]], 0, len - 1, prv[arr[i]], 0);

		prv[arr[i]] = i;
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b;

		a += ans;

		ans = get(tree[root[2 * b]], 0, len - 1, a, b);

		cout << ans << '\n';
	}
}
