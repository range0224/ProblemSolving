#include<iostream>
using namespace std;

int main()
{
	int n;
	int i;
	int cnt;

	cin >> n;

	n ^= -n;

	cnt = 0;
	for (i = 0; i < 32; i++)
	{
		cnt += n & 1;
		n >>= 1;
	}

	cout << cnt;
}
