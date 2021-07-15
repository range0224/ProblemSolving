#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
vector<pair<int, int>> v;
long long ans[100010];
int tree[SIZE];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
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
	int i;
	int x;
	int idx;
	long long cnt = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> x;

		v.push_back(make_pair(x, i));
	}

	sort(v.begin(), v.end());

	for (i = 1; i <= n; i++) update(i, 1);

	x = 1;
	idx = 1;
	for (i = 0; i < v.size(); i++)
	{
		if (v[i].first != x)
		{
			cnt += 1LL * get(1, 0, len - 1, idx, n);
			x++;
			idx = 1;
			cnt += 1LL * (v[i].first - x) * (n - i);
			x = v[i].first;
		}
		cnt += get(1, 0, len - 1, idx, v[i].second);

		ans[v[i].second] = cnt;
		x = v[i].first;
		idx = v[i].second;
		update(idx, 0);
	}

	for (i = 1; i <= n; i++)
	{
		cout << ans[i] << '\n';
	}
}
