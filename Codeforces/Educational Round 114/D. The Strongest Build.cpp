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
vector<int> v[15];
map<vector<int>, bool> mp;
map<vector<int>, bool> visited;
priority_queue<pair<long long, vector<int>>> pq;

int main()
{
	int i, j;
	int a, b;
	vector<int> tv;
	int cnt;
	long long d;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> a;
		for (j = 0; j < a; j++)
		{
			cin >> b;

			v[i].push_back(b);
		}
	}

	cin >> a;
	for (i = 0; i < a; i++)
	{
		tv.clear();
		for (j = 0; j < n; j++)
		{
			cin >> b;

			tv.push_back(b);
		}

		mp[tv] = true;
	}

	tv.clear();
	for (i = 0; i < n; i++)
	{
		tv.push_back(v[i].size());
	}

	d = 0;
	for (i = 0; i < n; i++) d += v[i][v[i].size() - 1];

	pq.push(make_pair(d, tv));
	while (!pq.empty())
	{
		d = pq.top().first;
		tv = pq.top().second;
		pq.pop();

		if (!mp[tv])
		{
			for (i = 0; i < n; i++)
			{
				cout << tv[i] << ' ';
			}
			return 0;
		}

		for (i = 0; i < n; i++)
		{
			if (tv[i] == 1) continue;

			tv[i]--;
			d -= v[i][tv[i]];
			if(tv[i]) d += v[i][tv[i] - 1];

			if (!visited[tv])
			{
				pq.push(make_pair(d, tv));
				visited[tv] = true;
			}

			d += v[i][tv[i]];
			if(tv[i]) d -= v[i][tv[i] - 1];
			tv[i]++;
		}
	}
}
