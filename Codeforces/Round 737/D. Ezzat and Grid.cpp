#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

const int SIZE = 1 << 21;
const int len = 1 << 20;
int n, m;
vector<pair<int, int>> v[300010];
vector<int> tv;
map<int, int> mp;
pair<int, int> tree[SIZE];
pair<int, int> lazy[SIZE];
int ans[300010];
int prv[300010];
bool visited[300010];

bool comp(pair<int, int> a, pair<int, int> b)
{
	return a.second < b.second;
}

void propagate(int idx)
{
	if (idx < len)
	{
		lazy[2 * idx] = max(lazy[2 * idx], lazy[idx]);
		lazy[2 * idx + 1] = max(lazy[2 * idx + 1], lazy[idx]);
	}
	tree[idx] = max(tree[idx], lazy[idx]);
	lazy[idx] = make_pair(0, 0);
}

void update(int idx, int s, int e, int ts, int te, pair<int, int> value)
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

	tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
}

pair<int, int> get(int idx, int s, int e, int ts, int te)
{
	int mid;

	propagate(idx);

	if (s > te || e < ts) return make_pair(0, 0);
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int i, j;
	int a, b, c;
	pair<int, int> p;
	int answer;
	int idx;

	cin >> n >> m;
	for (i = 0; i < m; i++)
	{
		cin >> a >> b >> c;

		v[a].push_back(make_pair(b, c));

		tv.push_back(b);
		tv.push_back(c);
	}

	sort(tv.begin(), tv.end());

	a = 2;
	mp[tv[0]] = 1;
	for (i = 1; i < tv.size(); i++)
	{
		if (tv[i] != tv[i - 1]) mp[tv[i]] = a++;
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < v[i].size(); j++)
		{
			v[i][j].first = mp[v[i][j].first];
			v[i][j].second = mp[v[i][j].second];
		}
	}

	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < v[i].size(); j++)
		{
			a = v[i][j].first;
			b = v[i][j].second;

			p = get(1, 0, len - 1, a, b);

			if (ans[i] < p.first + 1)
			{
				ans[i] = p.first + 1;
				prv[i] = p.second;
			}
		}

		for (j = 0; j < v[i].size(); j++)
		{
			update(1, 0, len - 1, v[i][j].first, v[i][j].second, make_pair(ans[i], i));
		}
	}

	answer = 0;
	for (i = 1; i <= n; i++)
	{
		if (answer < ans[i])
		{
			answer = ans[i];
			idx = i;
		}
	}

	while (idx != 0)
	{
		visited[idx] = true;
		idx = prv[idx];
	}

	cout << n - answer << '\n';
	for (i = 1; i <= n; i++)
	{
		if (!visited[i]) cout << i << ' ';
	}
}
