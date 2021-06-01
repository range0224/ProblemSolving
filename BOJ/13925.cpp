#include<iostream>
using namespace std;

const int MOD = 1000000007;
const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
long long tree[SIZE];
pair<long long, long long> lazy[SIZE];

void propagate(int idx, int s, int e)
{
	if (idx < len)
	{
		lazy[2 * idx].first *= lazy[idx].first;
		lazy[2 * idx].second *= lazy[idx].first;
		lazy[2 * idx].second += lazy[idx].second;

		lazy[2 * idx].first %= MOD;
		lazy[2 * idx].second %= MOD;

		lazy[2 * idx + 1].first *= lazy[idx].first;
		lazy[2 * idx + 1].second *= lazy[idx].first;
		lazy[2 * idx + 1].second += lazy[idx].second;

		lazy[2 * idx + 1].first %= MOD;
		lazy[2 * idx + 1].second %= MOD;
	}
	tree[idx] = lazy[idx].first * tree[idx] + lazy[idx].second * (e - s + 1);
	tree[idx] %= MOD;
	lazy[idx].first = 1;
	lazy[idx].second = 0;
}

void update(int idx, int s, int e, int ts, int te, int value, int option)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		if (option == 1) lazy[idx].second += value;
		else if (option == 2) lazy[idx].first *= value;
		else
		{
			lazy[idx].first = 0;
			lazy[idx].second = value;
		}

		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value, option);
	update(2 * idx + 1, mid + 1, e, ts, te, value, option);

	tree[idx] = (tree[2 * idx] + tree[2 * idx + 1]) % MOD;
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return (get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te)) % MOD;
}

int main()
{
	int i;
	int x;
	int q;
	int a, b, c, d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> x;

		update(1, 0, len - 1, i, i, x, 3);
	}

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a <= 3)
		{
			cin >> b >> c >> d;

			update(1, 0, len - 1, b, c, d, a);
		}
		else
		{
			cin >> b >> c;

			cout << get(1, 0, len - 1, b, c) << '\n';
		}
	}
}
