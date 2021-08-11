#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int SIZE = 1 << 14;
const int len = 1 << 13;
int n;
vector<pair<pair<int, int>, int>> v;
map<int, int> mp;
pair<pair<long long, long long>, pair<long long, long long>> tree[SIZE];

pair<pair<long long, long long>, pair<long long, long long>> make_node(pair<pair<long long, long long>, pair<long long, long long>> a, pair<pair<long long, long long>, pair<long long, long long>> b)
{
	pair<pair<long long, long long>, pair<long long, long long>> ret;

	ret.first.first = max(max(a.first.first, b.first.first), a.second.second + b.second.first);
	ret.first.second = a.first.second + b.first.second;
	ret.second.first = max(a.second.first, a.first.second + b.second.first);
	ret.second.second = max(b.second.second, b.first.second + a.second.second);

	return ret;
}

void update(int idx, int value)
{
	idx += len;
	tree[idx].first.first += value;
	tree[idx].first.second += value;
	tree[idx].second.first += value;
	tree[idx].second.second += value;
	idx /= 2;
	while (idx >= 1)
	{
		tree[idx] = make_node(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}

pair<pair<long long, long long>, pair<long long, long long>> get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return make_pair(make_pair(-(1LL << 50), 0), make_pair(-(1LL << 50), -(1LL << 50)));
	else if (ts <= s && e <= te) return tree[idx];

	mid = (s + e) / 2;

	return make_node(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}

int main()
{
	int i, j;
	int a, b, c;
	vector<int> tv;
	long long answer;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b >> c;

		v.push_back(make_pair(make_pair(a, b), c));
	}

	for (i = 0; i < n; i++)
	{
		tv.push_back(v[i].first.second);
	}

	sort(tv.begin(), tv.end());

	a = 2;
	mp[tv[0]] = 1;
	for (i = 1; i < tv.size(); i++)
	{
		if (tv[i] != tv[i - 1]) mp[tv[i]] = a++;
	}

	for (i = 0; i < v.size(); i++)
	{
		v[i].first.second = mp[v[i].first.second];
	}

	sort(v.begin(), v.end());

	answer = 0;
	for (i = 0; i < v.size(); i++)
	{
		if (i != 0 && v[i].first.first == v[i - 1].first.first) continue;

		for (j = i; j < v.size(); j++)
		{
			update(v[j].first.second, v[j].second);

			if(j == v.size()-1 || v[j].first.first != v[j+1].first.first) answer = max(answer, get(1, 0, len - 1, 1, mp.size()).first.first);
		}

		for (j = i; j < v.size(); j++)
		{
			update(v[j].first.second, -v[j].second);
		}
	}

	cout << answer;
}
