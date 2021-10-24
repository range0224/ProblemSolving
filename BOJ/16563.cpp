#include<iostream>
#include<vector>
using namespace std;

bool is_prime[2510];
vector<int> prime;

int main()
{
	int i, j;
	int t;
	int x;
	int a;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	is_prime[1] = true;
	for (i = 2; i * i <= 2500; i++)
	{
		if (is_prime[i]) continue;

		for (j = i * i; j <= 2500; j += i)
		{
			is_prime[j] = true;
		}
	}

	for (i = 2; i <= 2500; i++)
	{
		if (is_prime[i]) continue;

		prime.push_back(i);
	}

	cin >> t;
	while (t--)
	{
		cin >> x;

		a = x;
		for (i = 0; i < prime.size(); i++)
		{
			if (prime[i] * prime[i] > x) continue;

			while (a % prime[i] == 0)
			{
				cout << prime[i] << ' ';
				a /= prime[i];
			}
		}
		if (a != 1) cout << a;

		cout << '\n';
	}
}
