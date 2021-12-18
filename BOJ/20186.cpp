#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
int arr[5010];
int dp[5010][5010];

int recur(int cur, int cnt)
{
	if (cnt == m) return 0;
	else if (cur == n) return -10000000;

	if (dp[cur][cnt] != -1) return dp[cur][cnt];

	return dp[cur][cnt] = max(recur(cur + 1, cnt + 1) + arr[cur] - cnt, recur(cur + 1, cnt));
}

int main()
{
	int i;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	memset(dp, -1, sizeof(dp));

	cout << recur(0, 0);
}
