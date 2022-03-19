#include<iostream>
#include<algorithm>
using namespace std;

string a, b;
long long x;
int arr[20];
bool flag;

long long pows(long long x, long long y)
{
	long long ret;

	if (y == 0) return 1;

	ret = pows(x, y / 2);
	ret = min(2200000000LL, ret * ret);

	if (y % 2 == 0) return ret;
	else return min(2200000000LL, x * ret);
}

void recur(int cur, long long sum)
{
	int i;
	long long add;

	if (flag) return;

	if (cur == a.length())
	{
		if (sum == x)
		{
			for (i = 0; i < a.length(); i++)
			{
				cout << arr[i] << ' ';
			}
			flag = true;
		}
		return;
	}

	add = pows(10, a.length() - cur - 1);
	for (i = 0; i < 32; i++)
	{
		if (sum + add > x) break;

		arr[cur] = i;
		recur(cur + 1, sum + add);

		add = min(2200000000LL, add * (a[cur] - '0'));
	}
}

int main()
{
	int i;

	cin >> a >> b;

	for (i = 0; i < b.length(); i++)
	{
		x *= 10;
		x += b[i] - '0';
	}

	recur(0, 0);
}
