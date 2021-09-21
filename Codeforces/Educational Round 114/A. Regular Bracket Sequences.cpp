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

int main()
{
	int t;
	int i, j;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> n;

		for (i = 1; i <= n; i++)
		{
			for (j = 0; j < i; j++)
			{
				cout << '(';
			}
			for (j = i; j < 2 * i; j++)
			{
				cout << ')';
			}
			for (j = 2 * i; j < 2 * n; j += 2)
			{
				cout << "()";
			}
			cout << '\n';
		}
	}
}
