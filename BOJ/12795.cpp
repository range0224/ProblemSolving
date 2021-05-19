#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class line
{
private:
	long long a, b;
public:
	line() {}
	line(long long a, long long b)
	{
		this->a = a;
		this->b = b;
	}
	long long get(long long x)
	{
		return a * x + b;
	}
};

class node
{
public:
	long long s, e;
	line li;
	int l, r;
	node() {}
	node(long long s, long long e, line li, int l, int r)
	{
		this->s = s;
		this->e = e;
		this->li = li;
		this->l = l;
		this->r = r;
	}
};

const long long INF = 1LL << 60;
vector<node> v;

void update(int idx, line li)
{
	long long s, e;
	long long mid;
	line li2;
	line small, large;

	s = v[idx].s;
	e = v[idx].e;
	li2 = v[idx].li;

	if (li.get(s) > li2.get(s))
	{
		small = li2;
		large = li;
	}
	else
	{
		small = li;
		large = li2;
	}

	if (small.get(e) < large.get(e))
	{
		v[idx].li = large;
		return;
	}

	mid = (s + e) / 2;

	if (small.get(mid) < large.get(mid))
	{
		v[idx].li = large;
		if (v[idx].r == -1)
		{
			v[idx].r = v.size();
			v.push_back(node(mid+1, e, line(0, -INF), -1, -1));
		}
		update(v[idx].r, small);
	}
	else
	{
		v[idx].li = small;
		if (v[idx].l == -1)
		{
			v[idx].l = v.size();
			v.push_back(node(s, mid, line(0, -INF), -1, -1));
		}
		update(v[idx].l, large);
	}
}

long long get(int idx, long long x)
{
	long long s, e;
	long long mid;

	if (idx == -1) return -INF;

	s = v[idx].s;
	e = v[idx].e;

	mid = (s + e) / 2;

	if (x <= mid) return max(v[idx].li.get(x), get(v[idx].l, x));
	else return max(v[idx].li.get(x), get(v[idx].r, x));
}

int main()
{
	int q;
	long long a, b, c;

	v.push_back(node(-1000000000000LL, 1000000000000LL, line(0, -INF), -1, -1));

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> q;
	while (q--)
	{
		cin >> a;

		if (a == 1)
		{
			cin >> b >> c;

			update(0, line(b, c));
		}
		else
		{
			cin >> b;

			cout << get(0, b) << '\n';;
		}
	}
}
