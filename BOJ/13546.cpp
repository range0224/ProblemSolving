#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;

const int SQRT = 350;
const int SIZE = 1 << 18;
const int len = 1 << 17;
int n, m;
int arr[100010];
int tree[SIZE];
vector<pair<pair<int, int>, int>> v;
deque<int> dq[100010];
int ans[100010];

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first / SQRT < b.first.first / SQRT;
	else return a.first.second < b.first.second;
}

void update(int idx, int value)
{
	idx += len;

	while (idx >= 1)
	{
		tree[idx] += value;

		idx /= 2;
	}
}

int get(int idx, int s, int e)
{
	int mid;

	if (s == e) return s;

	mid = (s + e) / 2;

	if (tree[2 * idx + 1]) return get(2 * idx + 1, mid + 1, e);
	else return get(2 * idx, s, mid);
}

int main()
{
	int i;
	int q;
	int a, b;
	int answer = 0;
	int x;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}
	cin >> q;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;

		v.push_back(make_pair(make_pair(a, b), i));
	}

	sort(v.begin(), v.end(), comp);

	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		if (!dq[arr[i]].empty()) update(dq[arr[i]].back() - dq[arr[i]].front(), -1);

		dq[arr[i]].push_back(i);

		update(dq[arr[i]].back() - dq[arr[i]].front(), 1);

		answer = max(answer, dq[arr[i]].back() - dq[arr[i]].front());
	}
	ans[v[0].second] = answer;

	for (i = 1; i < v.size(); i++)
	{
		while (a > v[i].first.first)
		{
			a--;

			if (!dq[arr[a]].empty()) update(dq[arr[a]].back() - dq[arr[a]].front(), -1);

			dq[arr[a]].push_front(a);

			update(dq[arr[a]].back() - dq[arr[a]].front(), 1);

			answer = max(answer, dq[arr[a]].back() - dq[arr[a]].front());
		}
		while (b < v[i].first.second)
		{
			b++;

			if (!dq[arr[b]].empty()) update(dq[arr[b]].back() - dq[arr[b]].front(), -1);

			dq[arr[b]].push_back(b);

			update(dq[arr[b]].back() - dq[arr[b]].front(), 1);

			answer = max(answer, dq[arr[b]].back() - dq[arr[b]].front());
		}
		while (a < v[i].first.first)
		{
			x = dq[arr[a]].back() - dq[arr[a]].front();
			dq[arr[a]].pop_front();

			update(x, -1);

			if (!dq[arr[a]].empty()) update(dq[arr[a]].back() - dq[arr[a]].front(), 1);

			if (answer == x && !tree[x + len]) answer = get(1, 0, len - 1);

			a++;
		}
		while (b > v[i].first.second)
		{
			x = dq[arr[b]].back() - dq[arr[b]].front();
			dq[arr[b]].pop_back();

			update(x, -1);

			if (!dq[arr[b]].empty()) update(dq[arr[b]].back() - dq[arr[b]].front(), 1);

			if (answer == x && !tree[x + len]) answer = get(1, 0, len - 1);

			b--;
		}

		ans[v[i].second] = answer;
	}

	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
