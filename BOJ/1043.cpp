#include<iostream>
#include<vector>
using namespace std;

int n, m;
vector<int> v;
int arr[60][60];
int par[60];

int find(int x)
{
	if (par[x] == x) return x;
	else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
	a = find(a);
	b = find(b);

	par[a] = b;
}

int main()
{
	int i, j, k;
	int a, b;
	int cnt;

	cin >> n >> m;
	cin >> a;
	for (i = 0; i < a; i++)
	{
		cin >> b;

		v.push_back(b);
	}
	for (i = 0; i < m; i++)
	{
		cin >> a;

		arr[i][0] = a;
		for (j = 1; j <= a; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (i = 1; i <= n; i++) par[i] = i;

	for (i = 0; i < m; i++)
	{
		for (j = 1; j < arr[i][0]; j++)
		{
			union_(arr[i][j], arr[i][j + 1]);
		}
	}

	if (v.empty())
	{
		cout << m;
		return 0;
	}

	for (i = 0; i < v.size() - 1; i++)
	{
		union_(v[i], v[i + 1]);
	}

	cnt = 0;
	for (i = 0; i < m; i++)
	{
		if (find(arr[i][1]) != find(v[0])) cnt++;
	}

	cout << cnt;
}
