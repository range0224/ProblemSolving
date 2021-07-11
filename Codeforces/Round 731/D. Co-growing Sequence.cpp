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
 
int n;
int arr[200010];
 
int main()
{
	int t;
	int i;
	int x;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		x = arr[0];
		for (i = 0; i < n; i++)
		{
			cout << (x | arr[i]) - arr[i] << ' ';
			x |= arr[i];
		}
		cout << '\n';
	}
}
