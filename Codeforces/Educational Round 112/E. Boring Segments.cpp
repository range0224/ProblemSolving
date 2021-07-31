#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
 
const int SIZE = 1 << 21;
const int len = 1 << 20;
int n, m;
int tree[SIZE];
int lazy[SIZE];
vector<pair<pair<int, int>, int>> v;
 
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	return a.second < b.second;
}
 
void propagate(int idx)
{
	if (idx < len)
	{
		lazy[2 * idx] += lazy[idx];
		lazy[2 * idx + 1] += lazy[idx];
	}
	tree[idx] += lazy[idx];
	lazy[idx] = 0;
}
 
void update(int idx, int s, int e, int ts, int te, int value)
{
	int mid;
 
	propagate(idx);
 
	if (s > te || e < ts) return;
	else if (ts <= s && e <= te)
	{
		lazy[idx] = value;
		propagate(idx);
		return;
	}
 
	mid = (s + e) / 2;
 
	update(2 * idx, s, mid, ts, te, value);
	update(2 * idx + 1, mid + 1, e, ts, te, value);
 
	tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
}
 
int get(int idx, int s, int e, int ts, int te)
{
	int mid;
 
	propagate(idx);
 
	if (s > te || e < ts) return 1;
	else if (ts <= s && e <= te) return tree[idx];
 
	mid = (s + e) / 2;
 
	return min(get(2 * idx, s, mid, ts, te), get(2 * idx + 1, mid + 1, e, ts, te));
}
 
int check()
{
	int a, b, c;
	int s, e;
	int ans = 1000000;
 
	s = 0;
	e = 0;
	update(1, 0, len - 1, v[0].first.first, v[0].first.second, 1);
	while (e < n)
	{
		if (get(1, 0, len - 1, 1, m - 1) >= 1)
		{
			ans = min(ans, v[e].second - v[s].second);
 
			update(1, 0, len - 1, v[s].first.first, v[s].first.second, -1);
			s++;
		}
		else
		{
			e++;
			if (e < n)
			{
				update(1, 0, len - 1, v[e].first.first, v[e].first.second, 1);
			}
		}
	}
 
	return ans;
}
 
int main()
{
	int i;
	int a, b, c;
	int s, e;
	int mid;
	int ans;
 
	cin.tie(NULL);
	ios::sync_with_stdio(false);
 
	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> a >> b >> c;
 
		v.push_back(make_pair(make_pair(a, b - 1), c));
	}
 
	sort(v.begin(), v.end(), comp);
 
	cout << check();
}
