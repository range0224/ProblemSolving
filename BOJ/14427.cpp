#include<iostream>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
int tree[SIZE];

void update(int idx)
{
	idx += len;
	tree[idx] = idx - len;
	idx /= 2;
	while (idx >= 1)
	{
		if (arr[tree[2 * idx]] <= arr[tree[2 * idx + 1]]) tree[idx] = tree[2 * idx];
		else tree[idx] = tree[2 * idx + 1];

		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;
	int a, b;

	if (s > te || e < ts) return -1;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	a = get(2 * idx, s, mid, ts, te);
	b = get(2 * idx + 1, mid + 1, e, ts, te);

	if (a == -1) return b;
	else if (b == -1) return a;
	else if (arr[a] <= arr[b]) return a;
	else return b;
}

int main()
{
	int q;
	int i;
	int a, b, c;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		update(i);
	}

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			arr[b] = c;
			update(b);
		}
		else
		{
			cout << get(1, 0, len - 1, 1, n) << '\n';
		}
	}
}
