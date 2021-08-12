#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

typedef pair<pair<long long, long long>, pair<long long, long long>> pll;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
long long prefix[100010];
long long mxtree[SIZE];
long long mntree[SIZE];
pll tree[SIZE];

pll make_pll(pll a, pll b)
{
	pll ret;

	ret.first.first = max(max(a.first.first, b.first.first), a.second.second + b.second.first);
	ret.first.second = a.first.second + b.first.second;
	ret.second.first = max(a.second.first, a.first.second + b.second.first);
	ret.second.second = max(b.second.second, b.first.second + a.second.second);

	return ret;
}

void update(int idx, long long value)
{
	idx += len;
	tree[idx] = make_pair(make_pair(value, value), make_pair(value, value));
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = make_pll(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

pll get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return make_pair(make_pair(-(1LL << 60), 0), make_pair(-(1LL << 60), -(1LL << 60)));
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return make_pll(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

void update_mx(int idx, long long value)
{
	idx += len;
	while (idx >= 1)
	{
		mxtree[idx] = max(mxtree[idx], value);
		idx /= 2;
	}
}

long long get_mx(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return -(1LL << 60);
	else if (ts <= s && e <= te) return mxtree[idx];

	mid = (s + e) / 2;

	return max(get_mx(2 * idx, s, mid, ts, te), get_mx(2 * idx + 1, mid + 1, e, ts, te));
}

void update_mn(int idx, long long value)
{
	idx += len;
	while (idx >= 1)
	{
		mntree[idx] = min(mntree[idx], value);
		idx /= 2;
	}
}

long long get_mn(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 1LL << 60;
	else if (ts <= s && e <= te) return mntree[idx];

	mid = (s + e) / 2;

	return min(get_mn(2 * idx, s, mid, ts, te), get_mn(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int i;
	int a, b, c, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	for (i = 1; i <= n; i++)
	{
		prefix[i] = prefix[i - 1] + arr[i];
	}

	for (i = 1; i <= n; i++)
	{
		update(i, arr[i]);
	}
	
	for (i = 0; i < SIZE; i++)
	{
		mxtree[i] = -(1LL << 60);
		mntree[i] = 1LL << 60;
	}

	for (i = 1; i <= n; i++)
	{
		update_mx(i, prefix[i]);
	}

	for (i = 1; i <= n; i++)
	{
		update_mn(i, prefix[i]);
	}
	update_mn(0, 0);

	cin >> q;
	while (q--)
	{
		cin >> a >> b >> c >> d;

		if (b <= c) cout << get_mx(1, 0, len - 1, c, d) - get_mn(1, 0, len - 1, a - 1, b - 1) << '\n';
		else cout << max(max(get_mx(1, 0, len - 1, c, d) - get_mn(1, 0, len - 1, a - 1, c - 1), get_mx(1, 0, len - 1, b, d) - get_mn(1, 0, len - 1, a - 1, b - 1)), get(1, 0, len - 1, c, b).first.first) << '\n';
	}
}
