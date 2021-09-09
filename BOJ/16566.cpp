#include<iostream>
using namespace std;

const int SIZE = 1 << 23;
const int len = 1 << 22;
int n, m, k;
int tree[SIZE];

void update(int idx, int value)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx] += value;
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

int get_kth(int idx, int s, int e, int& x)
{
	int mid;

	if (s == e) return s;

	mid = (s + e) / 2;

	if (tree[2 * idx] >= x) return get_kth(2 * idx, s, mid, x);
	else
	{
		x -= tree[2 * idx];
		return get_kth(2 * idx + 1, mid + 1, e, x);
	}
}

int main()
{
	int i;
	int x;
	int ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	for (i = 0; i < m; i++)
	{
		cin >> x;

		update(x, 1);
	}
	for (i = 0; i < k; i++)
	{
		cin >> x;

		x = get(1, 0, len - 1, 0, x) + 1;
		ans = get_kth(1, 0, len - 1, x);
		update(ans, -1);

		cout << ans << '\n';
	}
}
