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
int arr[5][100010];
long long prefix[100010];
long long suffix[100010];
 
int main()
{
	int t;
	int i, j;
	long long mx;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 1; i <= 2; i++)
		{
			for (j = 1; j <= n; j++)
			{
				cin >> arr[i][j];
			}
		}
 
		prefix[0] = 0;
		for (i = 1; i <= n; i++)
		{
			prefix[i] = prefix[i - 1] + arr[2][i];
		}
		suffix[n + 1] = 0;
		for (i = n; i >= 1; i--)
		{
			suffix[i] = suffix[i + 1] + arr[1][i];
		}
 
		mx = 1LL << 60;
		for (i = 1; i <= n; i++)
		{
			mx = min(mx, max(prefix[i - 1], suffix[i + 1]));
		}
 
		cout << mx << '\n';
	}
}
