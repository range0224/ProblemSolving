#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

typedef struct node_t
{
	int value;
	int l;
	int r;
}node;

const int MOD = 1000000007;
const int SIZE = 1 << 20;
const int len = 1 << 19;
int n;
int arr[300010];
vector<pair<int, int>> query;
vector<pair<int, int>> v[300010];
long long answer[100010];
int tree[SIZE];
node tree2[8000010];
int root[300010];
int root2[300010];
int fact[300010];
int rev[300010];
int cnt = 1;

void make_tree(node& root, int s, int e, node* tree)
{
	int mid;

	root.value = 0;

	if (s == e) return;

	mid = (s + e) / 2;
	root.l = cnt++;
	root.r = cnt++;
	make_tree(tree[root.l], s, mid, tree);
	make_tree(tree[root.r], mid + 1, e, tree);
}

void update(node& prv, node& root, int s, int e, int idx, int value, node* tree)
{
	int mid;

	if (s == e)
	{
		root.value += value;
		root.value %= MOD;
		return;
	}

	mid = (s + e) / 2;

	if (idx <= mid)
	{
		root.l = cnt++;
		root.r = prv.r;
		tree[root.l].value = tree[prv.l].value;
		update(tree[prv.l], tree[root.l], s, mid, idx, value, tree);
	}
	else
	{
		root.l = prv.l;
		root.r = cnt++;
		tree[root.r].value = tree[prv.r].value;
		update(tree[prv.r], tree[root.r], mid + 1, e, idx, value, tree);
	}

	root.value = (tree[root.l].value + tree[root.r].value) % MOD;
}

int get(node& prv, node& root, int s, int e, int ts, int te, node* tree)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return root.value - prv.value;

	mid = (s + e) / 2;

	return (get(tree[prv.l], tree[root.l], s, mid, ts, te, tree) + get(tree[prv.r], tree[root.r], mid + 1, e, ts, te, tree)) % MOD;
}

void update(int idx)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx]++;
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i, j;
	int a, b;
	long long sum;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		rev[arr[i]] = i;
	}

	for (i = 1; i <= n; i++)
	{
		root[i] = cnt++;
	}

	a = 2;
	fact[n - 1] = 1;
	for (i = n - 2; i >= 1; i--)
	{
		fact[i] = (1LL * fact[i + 1] * a) % MOD;
		a++;
	}

	cnt = 1;
	root2[0] = 0;
	make_tree(tree2[0], 0, len - 1, tree2);
	for (i = 1; i <= n; i++)
	{
		root2[i] = cnt++;
		update(tree2[root2[i - 1]], tree2[root2[i]], 0, len - 1, arr[i], fact[i], tree2);
	}

	sum = 1;
	for (i = n; i >= 1; i--)
	{
		sum += (1LL * fact[i] * get(1, 0, len - 1, 1, arr[i])) % MOD;
		sum %= MOD;

		update(arr[i]);
	}

	memset(tree, 0, sizeof(tree));

	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));
		v[arr[a]].push_back(make_pair(a, i));
		v[arr[a]].push_back(make_pair(b, i));
		v[arr[b]].push_back(make_pair(a, i));
		v[arr[b]].push_back(make_pair(b, i));
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < v[i].size(); j++)
		{
			if (arr[v[i][j].first] == i)
			{
				answer[v[i][j].second] -= (1LL * fact[v[i][j].first] * get(1, 0, len - 1, v[i][j].first, n)) % MOD;
			}
			else
			{
				if(query[v[i][j].second].first == v[i][j].first) answer[v[i][j].second] += (1LL * fact[v[i][j].first] * get(1, 0, len - 1, v[i][j].first, n)) % MOD;
				else answer[v[i][j].second] += (1LL * fact[v[i][j].first] * get(1, 0, len - 1, v[i][j].first + 1, n)) % MOD;
			}
		}

		update(rev[i]);
	}

	for (i = 0; i < q; i++)
	{
		a = query[i].first;
		b = query[i].second;

		ans = sum;

		ans += answer[i];
		ans %= MOD;
		if (arr[a] < arr[b]) ans += get(tree2[root2[a]], tree2[root2[b - 1]], 0, len - 1, arr[a] + 1, arr[b] - 1, tree2);
		else ans -= get(tree2[root2[a]], tree2[root2[b - 1]], 0, len - 1, arr[b] + 1, arr[a] - 1, tree2);

		ans += 10LL * MOD;
		ans %= MOD;

		cout << ans << '\n';
	}
}
