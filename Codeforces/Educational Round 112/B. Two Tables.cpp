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
 
int n, m;
int w, h;
 
int main()
{
	int t;
	int a, b;
	int x1, y1, x2, y2;
 
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		cin >> x1 >> y1 >> x2 >> y2;
		cin >> w >> h;
 
		a = max(0, w - max(x1, n - x2));
		b = max(0, h - max(y1, m - y2));
 
		if ((x2 - x1) + w > n && (y2 - y1) + h > m) printf("-1\n");
		else if ((x2 - x1) + w > n) printf("%.9lf\n", 1.0 * b);
		else if ((y2 - y1) + h > m) printf("%.9lf\n", 1.0 * a);
		else printf("%.9lf\n", 1.0 * min(a, b));
	}
}
