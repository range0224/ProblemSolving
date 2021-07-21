#include<iostream>
using namespace std;

unsigned long long n, m;

unsigned long long check(unsigned long long x, int len)
{
	bool used[10] = { false };
	int i;
	int cnt;
	unsigned long long num = x;

	while (x)
	{
		used[x % 10] = true;
		x /= 10;
	}

	cnt = 0;
	for (i = 0; i < 10; i++)
	{
		cnt += used[i];
	}

	if (num == 0)
	{
		cnt = 0;
		used[0] = false;
	}

	if (cnt > m) return 0;
	else if (cnt == m)
	{
		for (i = 9; i >= 0; i--)
		{
			if (used[i]) break;
		}

		while (len--)
		{
			num *= 10;
			num += i;
		}

		return num;
	}
	else
	{
		if (m - cnt > len) return 0;

		if (!used[9])
		{
			num *= 10;
			num += 9;
			cnt++;
			len--;
			used[9] = true;
		}

		x = len - (m - cnt);
		while (x--)
		{
			num *= 10;
			num += 9;
			len--;
		}

		for (i = 9; i >= 0; i--)
		{
			if (len == 0) break;

			if (!used[i])
			{
				num *= 10;
				num += i;
				len--;
			}
		}

		return num;
	}
}

unsigned long long recur(int cur, unsigned long long num, int len)
{
	int i;
	unsigned long long ret;
	unsigned long long temp;

	ret = check(num, len - cur);
	if (ret < n) ret = 0;

	if (ret == 0) return 0;

	if (cur == len)
	{
		return ret;
	}

	for (i = 0; i <= 9; i++)
	{
		if (cur == 0 && i == 0) continue;

		temp = recur(cur + 1, 10 * num + i, len);

		if (temp != 0) return temp;
	}

	return ret;
}

int main()
{
	int i;
	unsigned long long temp;
	int len;

	cin >> n >> m;

	temp = n;
	len = 0;
	while (temp)
	{
		temp /= 10;
		len++;
	}

	for (i = len;; i++)
	{
		temp = recur(0, 0, i);

		if (temp != 0)
		{
			cout << temp;
			break;
		}
	}
}
