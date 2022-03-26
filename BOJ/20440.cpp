#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;
vector<int> tv;
int idx[2000010];
int cnt[2000010];
int len;

int get_idx(int v)
{
	int s, e;
	int mid;

	s = 0;
	e = len - 1;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (idx[mid] == v) return mid;
		else if (idx[mid] < v) s = mid + 1;
		else e = mid - 1;
	}
}

int main()
{
	int i, j;
	int a, b;
	int mx;
	int sum;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(a, b));
		tv.push_back(a);
		tv.push_back(b);
	}

	sort(tv.begin(), tv.end());

	idx[0] = tv[0];
	len = 1;
	for (i = 1; i < tv.size(); i++)
	{
		if (tv[i] == tv[i - 1]) continue;

		idx[len++] = tv[i];
	}

	for (i = 0; i < v.size(); i++)
	{
		cnt[get_idx(v[i].first)]++;
		cnt[get_idx(v[i].second)]--;
	}

	mx = -1;
	sum = 0;
	for (i = 0; i < 2000010; i++)
	{
		sum += cnt[i];

		if (mx < sum) mx = sum;
	}

	cout << mx << '\n';

	sum = 0;
	for (i = 0; i < 2000010; i++)
	{
		sum += cnt[i];

		if (sum == mx)
		{
			cout << idx[i] << ' ';

			for (j = i + 1; cnt[j] == 0; j++);

			cout << idx[j];
			return 0;
		}
	}
}
