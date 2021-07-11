#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
using namespace std;
 
const int SIZE = 1 << 20;
const int len = 1 << 19;
int n;
int arr[400010];
int tree[SIZE];
 
int gcd(int a, int b)
{
	int temp;
 
	while (a % b)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
 
	return b;
}
 
void update(int idx, int value)
{
	idx += len;
	tree[idx] = value;
	idx /= 2;
	while(idx >= 1)
	{
		tree[idx] = gcd(tree[2 * idx], tree[2 * idx + 1]);
		idx /= 2;
	}
}
 
int get(int idx, int s, int e, int ts, int te)
{
	int mid;
	int a, b;
 
	if (s > te || e < ts) return -1;
	else if (ts <= s && e <= te) return tree[idx];
 
	mid = (s + e) / 2;
 
	a = get(2 * idx, s, mid, ts, te);
	b = get(2 * idx + 1, mid + 1, e, ts, te);
 
	if (a != -1 && b != -1) return gcd(a, b);
	else if (a == -1) return b;
	else if (b == -1) return a;
	else return -1;
}
 
int main()
{
	int t;
	int i;
	int x, y;
	int s, e;
	int ans;
 
	for (i = 1; i < SIZE; i++) tree[i] = 1;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		for (i = 0; i < n; i++)
		{
			if (arr[i] != arr[0]) break;
		}
 
		if (i == n)
		{
			cout << 0 << '\n';
			continue;
		}
 
		x = arr[0];
		for (i = 1; i < n; i++)
		{
			x = gcd(x, arr[i]);
		}
 
		for (i = n; i < 2 * n; i++)
		{
			arr[i] = arr[i - n];
		}
 
		for (i = 1; i < 2 * n; i++) update(i, arr[i]);
 
		ans = 0;
		s = 0;
		e = 0;
		y = arr[0];
		while (s < n)
		{
			if (y == x)
			{
				ans = max(ans, e - s);
				s++;
				if (s > e) e++;
				y = get(1, 0, len - 1, s, e);
			}
			else
			{
				e++;
				y = gcd(y, arr[e]);
			}
		}
 
		cout << ans << '\n';
 
		for (i = 1; i < 2 * n; i++) update(i, 1);
	}
}
