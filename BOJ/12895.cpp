#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n, m;
int tree[SIZE];
int lazy[SIZE];

void propagate(int idx, int s, int e)
{
	if (lazy[idx] == -1) return;

	if (idx < len)
	{
		lazy[2 * idx] = lazy[idx];
		lazy[2 * idx + 1] = lazy[idx];
	}
	tree[idx] = 1 << lazy[idx];
	lazy[idx] = -1;
}

void update(int idx, int s, int e, int v, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = v;
		propagate(idx, s, e);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, v, ts, te);
	update(2 * idx + 1, mid + 1, e, v, ts, te);

	tree[idx] = tree[2 * idx] | tree[2 * idx + 1];
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx, s, e);

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) | get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int q;
	int i;
	string a;
	int b, c, d;
	int cnt;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	memset(lazy, -1, sizeof(lazy));

	cin >> n >> m >> q;
	update(1, 0, len - 1, 0, 1, n);
	while (q--)
	{
		cin >> a;

		if (a[0] == 'C')
		{
			cin >> b >> c >> d;

			if (b > c)
			{
				b ^= c;
				c ^= b;
				b ^= c;
			}

			update(1, 0, len - 1, d - 1, b, c);
		}
		else
		{
			cin >> b >> c;

			if (b > c)
			{
				b ^= c;
				c ^= b;
				b ^= c;
			}

			x = get(1, 0, len - 1, b, c);
			cnt = 0;
			while (x)
			{
				cnt += x % 2;
				x /= 2;
			}

			cout << cnt << '\n';
		}
	}
}
