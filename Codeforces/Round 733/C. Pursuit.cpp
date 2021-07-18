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
 
int n;
int a[100010];
int b[100010];
 
int main()
{
	int t;
	int i;
	int num;
	long long x, y;
	int idx, aidx;;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> a[i];
		}
		for (i = 0; i < n; i++)
		{
			cin >> b[i];
		}
 
		sort(a, a + n);
		sort(b, b + n);
 
		x = 0;
		y = 0;
		for (i = n / 4; i < n; i++)
		{
			x += a[i];
			y += b[i];
		}
 
		if (x >= y)
		{
			cout << 0 << '\n';
			continue;
		}
 
		aidx = n / 4;
		idx = n / 4 - 1;
		for (i = 1; i <= n + 100000; i++)
		{
			x += 100;
 
			if (idx >= 0) y += b[idx];
			idx--;
 
			if ((n + i) % 4 == 0)
			{
				if (aidx < n) x -= a[aidx++];
				else x -= 100;
 
				idx++;
				if(idx >= -1) y -= b[idx];
			}
 
			if (x >= y) break;
		}
 
		cout << i << '\n';
	}
}
