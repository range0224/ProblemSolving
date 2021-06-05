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
int arr[2010];
int arr2[2010];
 
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
 
int main()
{
	int t;
	int i, j;
	int idx;
	int ans;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		idx = 0;
		for (i = 0; i < n; i++)
		{
			if (arr[i] % 2 == 0) arr2[idx++] = arr[i];
		}
		for (i = 0; i < n; i++)
		{
			if (arr[i] % 2 == 1) arr2[idx++] = arr[i];
		}
		
		ans = 0;
		for (i = 0; i < n; i++)
		{
			for (j = i + 1; j < n; j++)
			{
				if (gcd(arr2[i], 2 * arr2[j]) > 1) ans++;
			}
		}
 
		cout << ans << '\n';
	}
}
