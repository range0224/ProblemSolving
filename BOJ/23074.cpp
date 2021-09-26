#include<iostream>
#include<set>
using namespace std;

int n;
int arr[500010];

int main()
{
	long long i, j;
	int num;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;

	arr[1] = 1;
	for (i = 2; i <= n; i += 2) arr[i] = i / 2;
	for (i = 3; i <= n; i += 2) arr[i] = i / 2;

	num = 1;
	for (i = 1; i <= n; i++)
	{
		if (num < arr[i]) num = arr[i];
	}

	cout << num << '\n';
	for (i = 1; i <= n; i++)
	{
		cout << arr[i] << ' ';
	}
}
