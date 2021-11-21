#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

const int MUL = 917;
const int MOD = 993244853;
int n;
string str;
long long hashing[1000010];
long long pows[1000010];
int ans;

long long get_hash(int s, int e)
{
	long long ret;

	ret = hashing[e] - hashing[s - 1] * pows[e - s + 1];
	ret %= MOD;
	ret += MOD;
	ret %= MOD;

	return ret;
}

bool same(int s1, int e1, int s2, int e2)
{
	return get_hash(s1, e1) == get_hash(s2, e2);
}

int main()
{
	int i;
	int idx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	cin >> str;

	str = '#' + str;

	pows[0] = 1;
	for (i = 1; i <= str.length(); i++) pows[i] = (pows[i - 1] * MUL) % MOD;

	hashing[0] = str[0];
	for (i = 1; i < str.length(); i++) hashing[i] = (hashing[i - 1] * MUL + str[i]) % MOD;

	idx = 0;
	for (i = n / 2; i >= 0; i--)
	{
		idx = min(n / 2 - i, idx + 2);

		if (!same(1, i, n - i + 1, n)) continue;

		ans = max(ans, i);

		while (idx >= 0 && !same(i + 1, i + idx, n - i - idx + 1, n - i)) idx--;

		ans = max(ans, i + idx);
	}

	cout << ans;
}
