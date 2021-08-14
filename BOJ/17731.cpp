#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<algorithm>
using namespace std;

const int SQRT = 320;
const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
long long arr[100010];
vector<pair<pair<int, int>, int>> v;
long long ans[100010];
map<int, int> mp;
long long rmp[100010];
vector<int> tv;
long long tree[SIZE];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

void update(int idx, int value)
{
	idx += len;
	tree[idx] += value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int q;
	int i;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	for (i = 1; i <= n; i++)
	{
		tv.push_back(arr[i]);
	}

	sort(tv.begin(), tv.end());

	a = 2;
	mp[tv[0]] = 1;
	rmp[1] = tv[0];
	for (i = 1; i < tv.size(); i++)
	{
		if (tv[i] != tv[i - 1])
		{
			rmp[a] = tv[i];
			mp[tv[i]] = a++;
		}
	}

	for (i = 1; i <= n; i++)
	{
		arr[i] = mp[arr[i]];
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		update(arr[i], rmp[arr[i]]);
	}

	ans[v[0].second] = get(1, 0, len - 1, 1, n);

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			update(arr[a], rmp[arr[a]]);
		}
		while (b < v[i].first.second)
		{
			b++;

			update(arr[b], rmp[arr[b]]);
		}
		while (a < v[i].first.first)
		{
			update(arr[a], -rmp[arr[a]]);

			a++;
		}
		while (b > v[i].first.second)
		{
			update(arr[b], -rmp[arr[b]]);

			b--;
		}

		ans[v[i].second] = get(1, 0, len - 1, 1, n);
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
