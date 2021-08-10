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
int arr[100010];
 
int main()
{
	int t;
	int i;
	long double ans;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		sort(arr, arr + n);
 
		ans = 0;
		for (i = 0; i < n - 1; i++)
		{
			ans += arr[i];
		}
		ans /= n - 1;
		ans += arr[n - 1];
 
		printf("%.12Lf\n", ans);
	}
}
