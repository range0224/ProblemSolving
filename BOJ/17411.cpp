#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MOD = 1000000007;
const int SIZE = 1 << 21;
const int len = 1 << 20;
int n;
int arr[1000010];
vector<pair<int, int>> v;
pair<int, long long> tree[SIZE];

bool comp(pair<int, int> a, pair<int, int> b)
{
	if (a.first != b.first) return a.first < b.first;
	else return a.second > b.second;
}

pair<int, long long> merge(pair<int, long long> a, pair<int, long long> b)
{
	if (a.first > b.first) return a;
	else if (a.first < b.first) return b;
	else return make_pair(a.first, (a.second + b.second) % MOD);
}

void update(int idx, pair<int, long long> value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

pair<int, long long> get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return make_pair(0, 0);
	else if(ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return merge(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int i;
	pair<int, long long> ans = make_pair(0, 1);
	pair<int, long long> ret;

	cin.tie(NULL);
	ios::sync_with_stdio(false);
	
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	for (i = 1; i <= n; i++)
	{
		v.push_back(make_pair(arr[i], i));
	}

	sort(v.begin(), v.end(), comp);

	update(0, make_pair(0, 1));

	for (i = 0; i < v.size(); i++)
	{
		ret = get(1, 0, len - 1, 0, v[i].second - 1);
		ret.first++;

		ans = merge(ans, ret);
		update(v[i].second, ret);
	}

	cout << ans.first << ' ' << ans.second % MOD;
}
