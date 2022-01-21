#include<iostream>
using namespace std;

long long n, m;
int arr[110];

bool check(int s, int e)
{
	if (s >= e) return true;
	
	if (arr[s] == arr[e]) return check(s + 1, e - 1);
	else return false;
}

int check()
{
	int idx = 0;

	while (n)
	{
		arr[idx++] = n % m;
		n /= m;
	}

	return check(0, idx - 1);
}

int main()
{
	int t;

	cin >> t;
	while (t--)
	{
		cin >> n >> m;

		cout << check() << '\n';
	}
}
