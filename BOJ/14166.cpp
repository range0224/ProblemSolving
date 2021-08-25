#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m;
vector<int> v[100010];
vector<int> gap[100010];
vector<int> first_gap;
long long sum;
long long total;
int cnt;

void recur(int cur, long long value)
{
	int i;
	int s, e;
	int mid;

	if (cnt >= m) return;

	if (cur != -1 && value < first_gap[cur])
	{
		s = 0;
		e = cur - 1;
		cur = -1;
		while (s <= e)
		{
			mid = (s + e) / 2;

			if (first_gap[mid] <= value)
			{
				cur = mid;
				s = mid + 1;
			}
			else e = mid - 1;
		}
	}

	if (cur == -1)
	{
		cnt++;
		return;
	}

	recur(cur - 1, value);
	for (i = 0; i < gap[cur].size(); i++)
	{
		if (value < gap[cur][i]) break;

		recur(cur - 1, value - gap[cur][i]);
	}
}

void get_ans(int cur, long long value)
{
	int i;
	int s, e;
	int mid;

	if (cur != -1 && value < first_gap[cur])
	{
		s = 0;
		e = cur - 1;
		cur = -1;
		while (s <= e)
		{
			mid = (s + e) / 2;

			if (first_gap[mid] <= value)
			{
				cur = mid;
				s = mid + 1;
			}
			else e = mid - 1;
		}
	}

	if (cur == -1)
	{
		total += value + 1;
		return;
	}

	get_ans(cur - 1, value);
	for (i = 0; i < gap[cur].size(); i++)
	{
		if (value < gap[cur][i]) break;

		get_ans(cur - 1, value - gap[cur][i]);
	}
}

int main()
{
	int i, j;
	int a, b;
	long long s, e;
	long long mid;
	long long ans;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b;

			sum += b;
			n--;
			i--;
			continue;
		}

		for (j = 0; j < a; j++)
		{
			cin >> b;

			v[i].push_back(b);
		}

		sort(v[i].begin(), v[i].end());

		sum += v[i][0];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 1; j < v[i].size(); j++)
		{
			gap[i].push_back(v[i][j] - v[i][0]);
		}
	}

	sort(gap, gap + n);

	for (i = 0; i < n; i++)
	{
		first_gap.push_back(gap[i][0]);
	}

	s = 0;
	e = 0;
	for (i = 0; i < n; i++)
	{
		e += gap[i].back();
	}
	while (s <= e)
	{
		mid = (s + e) / 2;

		cnt = 0;
		recur(n - 1, mid);

		if (cnt >= m)
		{
			ans = mid;
			e = mid - 1;
		}
		else s = mid + 1;
	}

	get_ans(n - 1, ans - 1);

	cout << (sum + ans) * m - total;
}
