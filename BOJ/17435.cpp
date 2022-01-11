#include<iostream>
using namespace std;

int n;
int nxt[30][200010];

int main()
{
	int q;
	int i, j;
	int a, b;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> nxt[0][i];
	}

	for (i = 1; i < 30; i++)
	{
		for (j = 1; j <= n; j++)
		{
			nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
		}
	}

	cin >> q;
	while (q--)
	{
		cin >> a >> b;

		for (i = 29; i >= 0; i--)
		{
			if (a & (1 << i)) b = nxt[i][b];
		}

		cout << b << '\n';
	}
}
