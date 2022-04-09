#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
int w[510][510];
bool merged[510];
bool visited[510];
int q[510];

int update(int v)
{
	int i;
	int mx = -(1 << 30);
	int idx;

	for (i = 1; i <= n; i++)
	{
		if (merged[i] || visited[i]) continue;

		q[i] += w[v][i];
		if (mx < q[i])
		{
			mx = q[i];
			idx = i;
		}
	}

	return idx;
}

int get_mincut()
{
	int i, j;
	int ans = 1 << 30;
	int prv, nxt;

	memset(merged, false, sizeof(merged));
	for (i = 0; i < n - 1; i++)
	{
		memset(visited, false, sizeof(visited));
		memset(q, 0, sizeof(q));

		for (j = 1; j <= n; j++)
		{
			if (!merged[j])
			{
				visited[j] = true;
				prv = j;
				nxt = update(j);
				break;
			}
		}

		for (j = 0; j < n - i - 2; j++)
		{
			visited[nxt] = true;
			prv = nxt;
			nxt = update(nxt);
		}

		ans = min(ans, q[nxt]);
		merged[nxt] = true;
		for (j = 1; j <= n; j++)
		{
			w[j][prv] += w[j][nxt];
			w[prv][j] += w[nxt][j];
		}
	}

	return ans;
}

int main()
{
	int t;
	int i;
	int a, b, c;

	cin >> t;
	while (t--)
	{
		memset(w, 0, sizeof(w));

		cin >> n >> m;
		for (i = 0; i < m; i++)
		{
			cin >> a >> b >> c;

			w[a][b] += c;
			w[b][a] += c;
		}

		cout << get_mincut() << '\n';
	}
}
