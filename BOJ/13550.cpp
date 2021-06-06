#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
const int SQRT = 350;
int n, m;
int arr[100010];
int prefix[100010];
vector<pair<pair<int, int>, int>> v;
int pos[1000010];
int pre[100010];
int nxt[100010];
int tree[SIZE];
int ans[100010];
pair<int, int> dq[1000010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

void update(int idx, int v)
{
	idx += len;
	
	while (idx >= 1)
	{
		tree[idx] += v;
		idx /= 2;
	}
}

int get(int idx, int s, int e)
{
	int mid;

	if (s == e) return s;

	mid = (s + e) / 2;
	if (tree[2 * idx + 1]) return get(2 * idx + 1, mid + 1, e);
	else return get(2 * idx, s, mid);
}

int main()
{
	int i;
	int a, b;
	int q;
	int answer = 0;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];

		arr[i] %= m;
	}

	for (i = 1; i <= n; i++)
	{
		prefix[i] = prefix[i - 1] + arr[i];
		prefix[i] %= m;
	}

	memset(pos, -1, sizeof(pos));
	for (i = 0; i <= n; i++)
	{
		pre[i] = pos[prefix[i]];
		pos[prefix[i]] = i;
	}

	memset(pos, -1, sizeof(pos));
	for (i = n; i >= 0; i--)
	{
		nxt[i] = pos[prefix[i]];
		pos[prefix[i]] = i;
	}

	for (i = 0; i <= 1000000; i++) dq[i] = make_pair(-1, -1);

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a - 1, b), i));
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		update(dq[prefix[i]].second - dq[prefix[i]].first, -1);
		if (dq[prefix[i]].first == -1) dq[prefix[i]].first = i;
		dq[prefix[i]].second = i;
		update(dq[prefix[i]].second - dq[prefix[i]].first, 1);
	}

	ans[v[0].second] = get(1, 0, len - 1);

	update(0, 1000000);

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;
			update(dq[prefix[a]].second - dq[prefix[a]].first, -1);
			dq[prefix[a]].first = a;
			if (dq[prefix[a]].second == -1) dq[prefix[a]].second = a;
			update(dq[prefix[a]].second - dq[prefix[a]].first, 1);
		}
		while (b < v[i].first.second)
		{
			b++;
			update(dq[prefix[b]].second - dq[prefix[b]].first, -1);
			if (dq[prefix[b]].first == -1) dq[prefix[b]].first = b;
			dq[prefix[b]].second = b;
			update(dq[prefix[b]].second - dq[prefix[b]].first, 1);
		}
		while (a < v[i].first.first)
		{
			update(dq[prefix[a]].second - dq[prefix[a]].first, -1);
			dq[prefix[a]].first = nxt[a];
			if (nxt[a] > b || nxt[a] == -1) dq[prefix[a]] = make_pair(-1, -1);
			update(dq[prefix[a]].second - dq[prefix[a]].first, 1);

			a++;
		}
		while (b > v[i].first.second)
		{
			update(dq[prefix[b]].second - dq[prefix[b]].first, -1);
			dq[prefix[b]].second = pre[b];
			if (pre[b] < a || pre[b] == -1) dq[prefix[b]] = make_pair(-1, -1);
			update(dq[prefix[b]].second - dq[prefix[b]].first, 1);

			b--;
		}

		ans[v[i].second] = get(1, 0, len - 1);
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
