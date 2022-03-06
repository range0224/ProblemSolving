#include<iostream>
#include<vector>
using namespace std;

int main()
{
	int n;
	int i, j;
	int cnt;
	vector<int> v;
	vector<int> ans;

	for (i = 2; i <= 120; i++)
	{
		cnt = 0;
		for (j = 1; j <= i; j++)
		{
			cnt += (i % j == 0);
		}

		if (cnt == 2) v.push_back(i);
	}

	for (i = 0; i < v.size() - 1; i++)
	{
		ans.push_back(v[i] * v[i + 1]);
	}

	cin >> n;

	for (i = 0; i < ans.size(); i++)
	{
		if (ans[i] > n)
		{
			cout << ans[i];
			break;
		}
	}
}
