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
 
vector<pair<int, int>> v;
 
int main()
{
	int t;
	int x;
	int i;
 
	cin >> t;
	while (t--)
	{
		v.clear();
		for (i = 0; i < 4; i++)
		{
			cin >> x;
 
			v.push_back(make_pair(x, i));
		}
 
		sort(v.begin(), v.end());
 
		if ((v[3].second <= 1 && v[2].second > 1) || (v[3].second > 1 && v[2].second <= 1)) cout << "YES\n";
		else cout << "NO\n";
	}
}
