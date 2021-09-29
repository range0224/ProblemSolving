#include<iostream>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
long long dp[5][100010];
long long tree[SIZE];

void init()
{
	int i;

	for (i = 0; i < SIZE; i++) tree[i] = 0;
}

void update(int idx, long long value)
{
	idx += len;
	while(idx >= 1)
	{
		tree[idx] += value;
		idx /= 2;
	}
}

long long get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if(ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int i;
	long long ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	for (i = 0; i < n; i++) dp[0][i] = 1;

	init();
	for (i = 0; i < n; i++)
	{
		dp[1][i] = get(1, 0, len - 1, arr[i] + 1, len - 1);
		update(arr[i], dp[0][i]);
	}

	init();
	ans = 0;
	for (i = 0; i < n; i++)
	{
		dp[2][i] = get(1, 0, len - 1, arr[i] + 1, len - 1);
		update(arr[i], dp[1][i]);

		ans += dp[2][i];
	}

	cout << ans;
}
