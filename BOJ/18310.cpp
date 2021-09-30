#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[200010];

int main()
{
	int i;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	sort(arr, arr + n);

	if (n % 2 == 0)
	{
		cout << arr[n / 2 - 1];
	}
	else
	{
		cout << arr[n / 2];
	}
}
