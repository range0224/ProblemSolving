#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
string str;
int tree[SIZE];
int lazy[SIZE];

void propagate(int idx)
{
	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += lazy[idx];
	lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;

	propagate(idx);

	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = value;
		propagate(idx);
		return;
	}

	mid = (s + e) / 2;

	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);

	tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx);

	if (s > te || e < ts) return 1 << 20;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return min(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int x;
	int i;
	int cnt = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> str;

	for (i = 0; i < str.length(); i++)
	{
		if (str[i] == '(') update(1, 0, len - 1, i, str.length() - 1, 1);
		else update(1, 0, len - 1, i, str.length() - 1, -1);
	}

	cin >> q;
	while (q--)
	{
		cin >> x;

		if (str[x - 1] == '(')
		{
			str[x - 1] = ')';

			update(1, 0, len - 1, x - 1, str.length() - 1, -2);
		}
		else
		{
			str[x - 1] = '(';

			update(1, 0, len - 1, x - 1, str.length() - 1, 2);
		}

		if (get(1, 0, len - 1, 0, str.length() - 1) == 0 && get(1, 0, len - 1, str.length() - 1, str.length() - 1) == 0) cnt++;
	}

	cout << cnt;
}
