#include<iostream>
using namespace std;

int n;
int l[100010];
int r[100010];
int par[100010];
bool visited[100010];
int arr[100010];
int idx;
int fin;

void inorder(int cur)
{
	if (cur == -1) return;

	inorder(l[cur]);
	arr[idx++] = cur;
	inorder(r[cur]);
}

int recur(int cur)
{
	visited[cur] = true;

	if (l[cur] != -1 && !visited[l[cur]]) return recur(l[cur]) + 1;
	else if (r[cur] != -1 && !visited[r[cur]]) return recur(r[cur]) + 1;
	else if (cur == fin) return 0;
	else return recur(par[cur]) + 1;
}

int main()
{
	int i;
	int a, b, c;
	int rt;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b >> c;

		l[a] = b;
		r[a] = c;
		if (b != -1) par[b] = a;
		if (c != -1) par[c] = a;
	}

	for (i = 1; i <= n; i++)
	{
		if (par[i] == 0)
		{
			rt = i;
			break;
		}
	}

	inorder(rt);

	fin = arr[idx - 1];

	cout << recur(rt);
}
