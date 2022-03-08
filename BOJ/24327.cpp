#include<iostream>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
string str;
int tree[SIZE];
int prefix[100010];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 1 << 30;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return min(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	cin >> str;

	str = '#' + str;

	for (i = 1; i < str.length(); i++)
	{
		if (str[i] == '(') prefix[i] = prefix[i - 1] + 1;
		else prefix[i] = prefix[i - 1] - 1;
	}
	for (i = 1; i < str.length(); i++)
	{
		update(i, prefix[i]);
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b;

		if (get(1, 0, len - 1, b, b) - get(1, 0, len - 1, a - 1, a - 1) == 0 && get(1, 0, len - 1, a, b) - get(1, 0, len - 1, a - 1, a - 1) >= 0) cout << 1 << '\n';
		else cout << 0 << '\n';
	}
}
