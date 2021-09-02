#include<iostream>
#include<vector>
using namespace std;

vector<pair<int, int>> v;

int main()
{
	int t;
	int n;
	int two, three;
	long long x;
	int cnt;
	int i;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		cin >> n;

		two = 0;
		three = 0;
		v.clear();
		while (n)
		{
			if (n % 2 == 0)
			{
				two++;
				n /= 2;
			}
			else if (n % 3 == 0)
			{
				three++;
				n /= 3;
			}
			else
			{
				x = 1;
				cnt = 0;
				while (x <= n)
				{
					x *= 3;
					cnt++;
				}
				x /= 3;
				cnt--;

				v.push_back(make_pair(two, three + cnt));
				n -= x;
			}
		}

		cout << v.size() << '\n';
		for (i = 0; i < v.size(); i++)
		{
			cout << v[i].first << ' ' << v[i].second << '\n';
		}
	}
}
