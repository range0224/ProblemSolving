#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SQRT = 350;
const int MAXV = 100010;
int n;
int arr[MAXV];
vector<int> v[MAXV];
int tour[2 * MAXV];
int in[MAXV], out[MAXV], depth[MAXV];
int par[20][MAXV];
bool visited[MAXV];
vector<pair<pair<int, int>, pair<int, int>>> query;
int idx;
int cnt[MAXV];
int cnt2[1000010];
int ans[MAXV];

bool comp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}

void dfs(int cur)
{
	int i;

	visited[cur] = true;
	in[cur] = idx;
	tour[idx] = cur;
	idx++;
	for (i = 0; i < v[cur].size(); i++)
	{
		if (visited[v[cur][i]]) continue;
		par[0][v[cur][i]] = cur;
		depth[v[cur][i]] = depth[cur] + 1;

		dfs(v[cur][i]);
	}
	out[cur] = idx;
	tour[idx] = cur;
	idx++;
}

int get_lca(int a, int b)
{
	int i;
	int gap;

	if (depth[a] < depth[b]) swap(a, b);

	gap = depth[a] - depth[b];
	for (i = 19; i >= 0; i--)
	{
		if (gap & (1 << i)) a = par[i][a];
	}

	for (i = 19; i >= 0; i--)
	{
		if (par[i][a] != par[i][b])
		{
			a = par[i][a];
			b = par[i][b];
		}
	}

	if (a == b) return a;
	else return par[0][a];
}

int main()
{
	int q;
	int i, j;
	int a, b;
	int lca;
	int answer;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	for (i = 0; i < n - 1; i++)
	{
		cin >> a >> b;

		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1);

	for (i = 1; i < 20; i++)
	{
		for (j = 1; j <= n; j++)
		{
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}

	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		if (in[a] > in[b]) swap(a, b);

		lca = get_lca(a, b);

		if (a == lca || b == lca)
		{
			query.push_back(make_pair(make_pair(in[a], in[b]), make_pair(i, -1)));
		}
		else
		{
			query.push_back(make_pair(make_pair(out[a], in[b]), make_pair(i, lca)));
		}
	}

	sort(query.begin(), query.end(), comp);

	answer = 0;
	a = query[0].first.first;
	b = query[0].first.second;
	for (i = a; i <= b; i++)
	{
		cnt[tour[i]]++;
		if (cnt[tour[i]] == 1)
		{
			cnt2[arr[tour[i]]]++;
			if (cnt2[arr[tour[i]]] == 1) answer++;
		}
		else
		{
			cnt2[arr[tour[i]]]--;
			if (cnt2[arr[tour[i]]] == 0) answer--;
		}
	}
	if (query[0].second.second != -1)
	{
		lca = query[0].second.second;

		cnt2[arr[lca]]++;
		if (cnt2[arr[lca]] == 1) answer++;
	}

	ans[query[0].second.first] = answer;

	for (i = 1; i < q; i++)
	{
		if (query[i - 1].second.second != -1)
		{
			lca = query[i - 1].second.second;

			cnt2[arr[lca]]--;
			if (cnt2[arr[lca]] == 0) answer--;
		}

		while (a > query[i].first.first)
		{
			a--;

			cnt[tour[a]]++;
			if (cnt[tour[a]] == 1)
			{
				cnt2[arr[tour[a]]]++;
				if (cnt2[arr[tour[a]]] == 1) answer++;
			}
			else
			{
				cnt2[arr[tour[a]]]--;
				if (cnt2[arr[tour[a]]] == 0) answer--;
			}
		}
		while (b < query[i].first.second)
		{
			b++;

			cnt[tour[b]]++;
			if (cnt[tour[b]] == 1)
			{
				cnt2[arr[tour[b]]]++;
				if (cnt2[arr[tour[b]]] == 1) answer++;
			}
			else
			{
				cnt2[arr[tour[b]]]--;
				if (cnt2[arr[tour[b]]] == 0) answer--;
			}
		}
		while (a < query[i].first.first)
		{
			cnt[tour[a]]--;
			if (cnt[tour[a]] == 1)
			{
				cnt2[arr[tour[a]]]++;
				if (cnt2[arr[tour[a]]] == 1) answer++;
			}
			else
			{
				cnt2[arr[tour[a]]]--;
				if (cnt2[arr[tour[a]]] == 0) answer--;
			}

			a++;
		}
		while (b > query[i].first.second)
		{
			cnt[tour[b]]--;
			if (cnt[tour[b]] == 1)
			{
				cnt2[arr[tour[b]]]++;
				if (cnt2[arr[tour[b]]] == 1) answer++;
			}
			else
			{
				cnt2[arr[tour[b]]]--;
				if (cnt2[arr[tour[b]]] == 0) answer--;
			}

			b--;
		}

		if (query[i].second.second != -1)
		{
			lca = query[i].second.second;

			cnt2[arr[lca]]++;
			if (cnt2[arr[lca]] == 1) answer++;
		}

		ans[query[i].second.first] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
