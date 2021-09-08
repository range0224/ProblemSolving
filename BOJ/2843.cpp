#include<iostream>
#include<vector>
using namespace std;

int n;
int arr[300010];
bool erased[300010];
vector<pair<int, int>> query;
int par[300010];
int ans[300010];

int find(int x)
{
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	if (a == b) par[a] = 0;
	else par[a] = b;
}

int main()
{
	int q;
	int i;
	int a, b;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		query.push_back(make_pair(a, b));

		if (a == 2) erased[b] = true;
	}

	for (i = 1; i <= n; i++)
	{
		par[i] = i;
	}

	for (i = 1; i <= n; i++)
	{
		if (arr[i] && !erased[i]) union_(i, arr[i]);
	}

	idx = 0;
	for (i = q - 1; i >= 0; i--)
	{
		if(query[i].first == 1) ans[idx++] = find(query[i].second);
		else union_(query[i].second, arr[query[i].second]);
	}

	for (i = idx - 1; i >= 0; i--)
	{
		if (ans[i]) cout << ans[i] << '\n';
		else cout << "CIKLUS\n";
	}
}
