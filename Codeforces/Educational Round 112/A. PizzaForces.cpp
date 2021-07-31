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
 
long long n;
 
int main()
{
	int t;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
 
		if (n <= 6) cout << 15 << '\n';
		else cout << ((n + 1) / 2) * 5 << '\n';
	}
}
