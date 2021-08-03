#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int SIZE = 1 << 21;
const int len = 1 << 20;
int n, m;
int arr[200010];
int tarr[200010];
vector<pair<int, int>> v;
vector<pair<int, int>> tv;
vector<int> nums;
map<int, int> mp;
int tree[SIZE];
vector<int> mgtree[SIZE];

void make_tree()
{
	int i;
	int a, b;

	for (i = 0; i < m; i++)
	{
		mgtree[len + i].push_back(tarr[i]);
	}

	for (i = len - 1; i >= 1; i--)
	{
		a = 0;
		b = 0;
		while (a < mgtree[2 * i].size() && b < mgtree[2 * i + 1].size())
		{
			if (mgtree[2 * i][a] < mgtree[2 * i + 1][b]) mgtree[i].push_back(mgtree[2 * i][a++]);
			else mgtree[i].push_back(mgtree[2 * i + 1][b++]);
		}
		while (a < mgtree[2 * i].size()) mgtree[i].push_back(mgtree[2 * i][a++]);
		while (b < mgtree[2 * i + 1].size()) mgtree[i].push_back(mgtree[2 * i + 1][b++]);
	}
}

int get_cnt(int idx, int s, int e, int ts, int te, int value)
{
	int mid;
	int ret;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te)
	{
		s = 0;
		e = mgtree[idx].size() - 1;
		ret = mgtree[idx].size();
		while (s <= e)
		{
			mid = (s + e) / 2;

			if (mgtree[idx][mid] < value) s = mid + 1;
			else
			{
				ret = mid;
				e = mid - 1;
			}
		}

		return mgtree[idx].size() - ret;
	}

	mid = (s + e) / 2;

	return get_cnt(2 * idx, s, mid, ts, te, value) + get_cnt(2 * idx + 1, mid + 1, e, ts, te, value);
}

void update(int idx, int value)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx] = max(tree[idx], value);
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return -1;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int i;
	int a, b;
	long long ans = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	memset(tree, -1, sizeof(tree));

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;
		
		v.push_back(make_pair(a, b));

		nums.push_back(a);
		nums.push_back(b);
	}
	for (i = 0; i < m; i++)
	{
		cin >> arr[i];

		nums.push_back(arr[i]);
	}

	sort(nums.begin(), nums.end());

	mp[nums[0]] = 1;
	a = 2;
	for (i = 1; i < nums.size(); i++)
	{
		if (nums[i] == nums[i - 1]) continue;

		mp[nums[i]] = a++;
	}

	for (i = 0; i < v.size(); i++)
	{
		tv.push_back(make_pair(mp[v[i].first], mp[v[i].second]));
	}
	for (i = 0; i < m; i++)
	{
		tarr[i] = mp[arr[i]];
	}

	for (i = 0; i < m; i++)
	{
		update(tarr[i], i);
	}

	make_tree();
	for (i = 0; i < n; i++)
	{
		a = get(1, 0, len - 1, min(tv[i].first, tv[i].second), max(tv[i].first, tv[i].second) - 1);
		b = get_cnt(1, 0, len - 1, a + 1, m - 1, max(tv[i].first, tv[i].second));

		if (a == -1)
		{
			if (b % 2 == 0) ans += v[i].first;
			else ans += v[i].second;
		}
		else
		{
			if (b % 2 == 0) ans += max(v[i].first, v[i].second);
			else ans += min(v[i].first, v[i].second);
		}
	}

	cout << ans;
}
