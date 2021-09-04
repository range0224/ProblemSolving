#include<iostream>
using namespace std;

int n;
long double arr[100010];

int main()
{
	int i;
	long double ans;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	ans = 0;
	for (i = 0; i < n; i++)
	{
		ans += arr[i];
	}

	for (i = 1; i < n; i++)
	{
		ans += arr[i - 1] * (1 - arr[i]) + arr[i] * (1 - arr[i - 1]);
	}

	printf("%.8Lf", ans);
}
