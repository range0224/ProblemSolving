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
 
int main()
{
	int t;
	int ax, ay;
	int bx, by;
	int fx, fy;
 
	cin >> t;
	while (t--)
	{
		cin >> ax >> ay >> bx >> by >> fx >> fy;
 
		if (ax == bx && bx == fx && ((ay <= fy && fy <= by) || (by <= fy && fy <= ay))) cout << abs(ay - by) + 2 << '\n';
		else if (ay == by && by == fy && ((ax <= fx && fx <= bx) || (bx <= fx && fx <= ax))) cout << abs(ax - bx) + 2 << '\n';
		else cout << abs(ax - bx) + abs(ay - by) << '\n';
	}
}
