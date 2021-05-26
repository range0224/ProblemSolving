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

const int MOD = 1000000007;
int n;
vector<pair<long long, long long>> v;
int arr[10];
long long ans;
bool visited[50];
long long dp[50][50][50][50];

int ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3)
{
	long long temp = 1LL * (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

	if (temp > 0) return 1;
	else if (temp == 0) return 0;
	else return -1;
}

bool in_tri(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3, long long x, long long y)
{
	if (ccw(x1, y1, x2, y2, x, y) == 1 && ccw(x2, y2, x3, y3, x, y) == 1 && ccw(x3, y3, x1, y1, x, y) == 1)
	{
		return true;
	}
	else if (ccw(x1, y1, x2, y2, x, y) == -1 && ccw(x2, y2, x3, y3, x, y) == -1 && ccw(x3, y3, x1, y1, x, y) == -1)
	{
		return true;
	}

	return false;
}

long long recur2(int cur)
{
	long long x1, x2, x3;
	long long y1, y2, y3;
	long long x, y;
	int i;
	long long temp;
	long long ret = 0;

	if (cur == n)
	{
		return 6;
	}

	if (dp[cur][arr[0]][arr[1]][arr[2]] != -1) return dp[cur][arr[0]][arr[1]][arr[2]];

	x1 = v[arr[0]].first;
	y1 = v[arr[0]].second;
	x2 = v[arr[1]].first;
	y2 = v[arr[1]].second;
	x3 = v[arr[2]].first;
	y3 = v[arr[2]].second;

	for (i = 0; i < n; i++)
	{
		if (visited[i]) continue;

		x = v[i].first;
		y = v[i].second;

		if (in_tri(x1, y1, x2, y2, x3, y3, x, y))
		{
			visited[i] = true;
			ret += recur2(cur + 1);
			visited[i] = false;
		}
		else if (in_tri(x1, y1, x2, y2, x, y, x3, y3))
		{
			temp = arr[2];
			arr[2] = i;
			visited[i] = true;
			ret += recur2(cur + 1);
			arr[2] = temp;
			visited[i] = false;
		}
		else if (in_tri(x1, y1, x3, y3, x, y, x2, y2))
		{
			temp = arr[1];
			arr[1] = i;
			visited[i] = true;
			ret += recur2(cur + 1);
			arr[1] = temp;
			visited[i] = false;
		}
		else if (in_tri(x2, y2, x3, y3, x, y, x1, y1))
		{
			temp = arr[0];
			arr[0] = i;
			visited[i] = true;
			ret += recur2(cur + 1);
			arr[0] = temp;
			visited[i] = false;
		}
	}

	return dp[cur][arr[0]][arr[1]][arr[2]] = ret % MOD;
}


void recur(int cur, int cnt)
{
	if (cnt == 3)
	{
		ans += recur2(3);
		ans %= MOD;
		return;
	}

	if (cur == n) return;

	arr[cnt] = cur;
	visited[cur] = true;
	recur(cur + 1, cnt + 1);
	visited[cur] = false;
	recur(cur + 1, cnt);
}

int main()
{
	int i, j, k;
	long long a, b;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a, b));
	}

	memset(dp, -1, sizeof(dp));

	recur(0, 0);

	cout << ans;
}
