#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int MAXV = 100010;
int n;
int arr[MAXV];
int in[MAXV], out[MAXV];
vector<pair<int, int>> cow;
vector<int> v[MAXV];
bool visited[MAXV];
int cnt;
int tree[SIZE];
int ans[MAXV];

bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.first > b.first;
}

void update(int idx)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx]++;
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

void dfs(int cur)
{
	int i;

	in[cur] = cnt++;
	for (i = 0; i < v[cur].size(); i++)
	{
		dfs(v[cur][i]);
	}
	out[cur] = cnt - 1;
}

int main()
{
	int i;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		cow.push_back(make_pair(arr[i], i));
	}
	for (i = 2; i <= n; i++)
	{
		cin >> x;

		v[x].push_back(i);
	}

	dfs(1);

	sort(cow.begin(), cow.end(), comp);

	for (i = 0; i < n; i++)
	{
		ans[cow[i].second] = get(1, 0, len - 1, in[cow[i].second] + 1, out[cow[i].second]);
		update(in[cow[i].second]);
	}

	for (i = 1; i <= n; i++)
	{
		cout << ans[i] << '\n';
	}
}
