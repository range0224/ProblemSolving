#include<iostream>
#include<algorithm>
using namespace std;

class line
{
public:
	long long a, b;
	double x;

	line() {}
	line(long long a, long long b, double x)
	{
		this->a = a;
		this->b = b;
		this->x = x;
	}
	long long get(long long v)
	{
		return a * v + b;
	}
};

const long long INF = 1000000000000000000LL;
int n;
long long a[100010];
long long b[100010];
long long ans;
line lines[100010];
int idx;

double get_x(long long a, long long b, long long c, long long d)
{
	return 1.0 * (d - b) / (a - c);
}

bool check(long long a, long long b, long long c, long long d, long long e, long long f)
{
	return get_x(a, b, c, d) >= get_x(a, b, e, f);
}

long long get(long long x)
{
	int s, e, mid;
	long long ret = INF;

	s = 0;
	e = idx - 1;
	while (s <= e)
	{
		mid = (s + e) / 2;

		if (lines[mid].x <= x)
		{
			ret = lines[mid].get(x);
			s = mid + 1;
		}
		else e = mid - 1;
	}

	return ret;
}

int main()
{
	int i, j;
	long long x, y;
	long long tx, ty;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (i = 0; i < n; i++)
	{
		cin >> b[i];
	}

	lines[idx++] = line(b[0], 0, -1000000000);
	for (i = 1; i < n; i++)
	{
		x = b[i];
		y = get(a[i]);

		while (idx >= 2 && check(lines[idx - 2].a, lines[idx - 2].b, lines[idx - 1].a, lines[idx - 1].b, x, y)) idx--;
		lines[idx++] = line(x, y, get_x(lines[idx - 1].a, lines[idx - 1].b, x, y));
	}

	cout << lines[idx - 1].b;
}
