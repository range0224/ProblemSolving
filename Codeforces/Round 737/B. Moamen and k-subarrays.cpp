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

int n, m;
int arr[100010];
vector<pair<int, int>> v;

int main()
{
	int t;
	int i;
	int cnt;

	cin >> t;
	while (t--)
	{
		v.clear();

		cin >> n >> m;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];

			v.push_back(make_pair(arr[i], i));
		}

		sort(v.begin(), v.end());

		cnt = 1;
		for (i = 1; i < n; i++)
		{
			if (v[i].second != v[i - 1].second + 1) cnt++;
		}

		if (cnt <= m) cout << "Yes\n";
		else cout << "No\n";
	}
}
