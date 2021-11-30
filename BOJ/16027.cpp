#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 20;
const int len = 1 << 19;

int n, m;
int arr[200010];
vector<pair<int, int>> v;
int tree[SIZE];

void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return max(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int i;
	int idx;
	int s, e;
	int mid;
	int ans;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	v.push_back(make_pair(arr[0], 1));
	for (i = 1; i < n; i++)
	{
		auto it = lower_bound(v.begin(), v.end(), make_pair(arr[i], -2000000000));

		if (it == v.end())
		{
			v.push_back(make_pair(arr[i], get(1, 0, len - 1, 0, v.size() - 1) + 1));
			update(v.size() - 1, v.back().second);
		}
		else
		{
			idx = it - v.begin();

			ans = -1;
			s = 0;
			e = v.size() - 1;
			while (s <= e)
			{
				mid = (s + e) / 2;

				if (v[mid].first <= arr[i] + m - 1)
				{
					ans = mid;
					s = mid + 1;
				}
				else e = mid - 1;
			}

			if (idx == 0) v[0] = make_pair(arr[i], ans + 2);
			else v[idx] = make_pair(arr[i], max(ans + 2, get(1, 0, len - 1, 0, idx - 1) + 1));

			update(idx, v[idx].second);
		}
	}

	ans = v.size();
	for (i = 0; i < v.size(); i++)
	{
		ans = max(ans, v[i].second);
	}

	cout << ans;
}
