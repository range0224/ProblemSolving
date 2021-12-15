#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
int A, B;
int arr[110][4];
int dp[110][110][110][5];

int recur(int cur, int a, int b, int c)
{
	if (cur == n)
	{
		if (b >= B) return 0;
		else return -1000000000;
	}

	if (dp[cur][a][b][c] != -1) return dp[cur][a][b][c];

	dp[cur][a][b][c] = recur(cur + 1, a, b + 1, 0) + max(arr[cur][0], arr[cur][1]);
	if(a < A) dp[cur][a][b][c] = max(dp[cur][a][b][c], recur(cur + 1, a + 1, b, 0) + arr[cur][3]);
	if(!c) dp[cur][a][b][c] = max(dp[cur][a][b][c], recur(cur + 1, a, b, 1) + arr[cur][2]);

	return dp[cur][a][b][c];
}

int main()
{
	int i, j;

	cin >> n >> A >> B;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 4; j++)
		{
			cin >> arr[i][j];
		}
	}

	memset(dp, -1, sizeof(dp));

	cout << recur(0, 0, 0, 0);
}
