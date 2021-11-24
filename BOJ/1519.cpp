#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
int dp[1000010];
vector<int> v;

void get_list(int num, int len)
{
	int i;
	int arr[10];
	int idx = 0;
	int x;
	int mod;

	while (num)
	{
		arr[idx++] = num % 10;
		num /= 10;
	}

	if (idx <= len) return;

	x = 0;
	mod = 1;
	for (i = idx - 1; i >= idx - len; i--)
	{
		x *= 10;
		x += arr[i];

		mod *= 10;
	}
	v.push_back(x);

	for (i = idx - len - 1; i >= 0; i--)
	{
		x *= 10;
		x %= mod;
		x += arr[i];

		v.push_back(x);
	}
}

int main()
{
	int i, j, k;

	cin >> n;

	memset(dp, -1, sizeof(dp));

	for (i = 10; i <= n; i++)
	{
		for (j = 1;; j++)
		{
			v.clear();

			get_list(i, j);

			if (v.empty()) break;

			sort(v.begin(), v.end());

			for (k = 0; k < v.size(); k++)
			{
				if (v[k] == 0) continue;

				if (dp[i - v[k]] == -1)
				{
					dp[i] = v[k];
					break;
				}
			}

			if (dp[i] != -1) break;
		}
	}

	cout << dp[n];
}
