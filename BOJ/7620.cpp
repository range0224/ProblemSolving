#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string a, b;

void recur(int s1, int e1, int s2, int e2)
{
	int mid;
	int i, j;
	int dp1[2][17010] = { 0 };
	int dp2[2][17010] = { 0 };
	int idx1, idx2;
	int ans;
	int mn;
	bool same;

	if (s1 > e1)
	{
		for (j = s2; j <= e2; j++)
		{
			cout << "a " << b[j] << '\n';
		}
		return;
	}
	else if (s2 > e2)
	{
		for (i = s1; i <= e1; i++)
		{
			cout << "d " << a[i] << '\n';
		}
        return;
	}
	else if (s1 == e1)
	{
		same = false;
		for (j = s2; j <= e2; j++)
		{
			if (a[s1] == b[j])
			{
				same = true;
				break;
			}
		}

		if (same)
		{
			for (j = s2; j <= e2; j++)
			{
				if (a[s1] == b[j])
				{
					cout << "c " << a[s1] << '\n';
					break;
				}

				cout << "a " << b[j] << '\n';
			}
			for (j++; j <= e2; j++)
			{
				cout << "a " << b[j] << '\n';
			}
		}
		else
		{
			cout << "m " << b[s2] << '\n';
			for (j = s2 + 1; j <= e2; j++)
			{
				cout << "a " << b[j] << '\n';
			}
		}

		return;
	}
	else if (s2 == e2)
	{
		same = false;
		for (i = s1; i <= e1; i++)
		{
			if (a[i] == b[s2])
			{
				same = true;
				break;
			}
		}

		if (same)
		{
			for (i = s1; i <= e1; i++)
			{
				if (a[i] == b[s2])
				{
					cout << "c " << a[i] << '\n';
					break;
				}

				cout << "d " << a[i] << '\n';
			}
			for (i++; i <= e1; i++)
			{
				cout << "d " << a[i] << '\n';
			}
		}
		else
		{
			cout << "m " << b[s2] << '\n';
			for (i = s1 + 1; i <= e1; i++)
			{
				cout << "d " << a[i] << '\n';
			}
		}

		return;
	}

	mid = (s1 + e1) / 2;

	idx1 = 1;
	for (j = s2; j <= e2; j++) dp1[idx1][j] = j - s2 + 1;
	for (i = s1; i <= mid; i++)
	{
		idx1 = !idx1;

		dp1[idx1][s2 - 1] = i - s1 + 1;

		for (j = s2; j <= e2; j++)
		{
			if (a[i] == b[j]) dp1[idx1][j] = dp1[!idx1][j - 1];
			else dp1[idx1][j] = min(min(dp1[!idx1][j], dp1[idx1][j - 1]), dp1[!idx1][j - 1]) + 1;
		}
	}

	idx2 = 1;
	for (j = e2; j >= s2; j--) dp2[idx2][j] = e2 - j + 1;
	for (i = e1; i >= mid + 1; i--)
	{
		idx2 = !idx2;

		dp2[idx2][e2 + 1] = e1 - i + 1;

		for (j = e2; j >= s2; j--)
		{
			if (a[i] == b[j]) dp2[idx2][j] = dp2[!idx2][j + 1];
			else dp2[idx2][j] = min(min(dp2[!idx2][j], dp2[idx2][j + 1]), dp2[!idx2][j + 1]) + 1;
		}
	}

	mn = 50000;
	ans = 0;
	for (j = s2 - 1; j <= e2; j++)
	{
		if (mn > dp1[idx1][j] + dp2[idx2][j + 1])
		{
			mn = dp1[idx1][j] + dp2[idx2][j + 1];
			ans = j;
		}
	}
	recur(s1, mid, s2, ans);
	recur(mid + 1, e1, ans + 1, e2);
}

int main()
{
	cin >> a >> b;

	a = '#' + a;
	b = '#' + b;

	recur(1, a.length() - 1, 1, b.length() - 1);
}
