#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[1010];

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
	int i;
	int ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	ans = 0;
	for (i = 1; i < n; i++)
	{
		if (!ans) ans = arr[i] - arr[i - 1];
		else if(arr[i] != arr[i - 1]) ans = gcd(ans, arr[i] - arr[i - 1]);
	}

	cout << ans;
}
