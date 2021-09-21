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

int a, b, c, x;
int arr[3];

int main()
{
	int t;
	int mn, mx;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> arr[0] >> arr[1] >> arr[2] >> x;

		sort(arr, arr + 3);

		mn = max(0, arr[2] - (arr[0] + arr[1] + 1));
		mx = max(0, arr[0] - 1) + max(0, arr[1] - 1) + max(0, arr[2] - 1);

		if (mn <= x && x <= mx) cout << "YES\n";
		else cout << "NO\n";
	}
}
