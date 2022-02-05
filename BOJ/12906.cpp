#include<iostream>
#include<string>
#include<queue>
#include<map>
using namespace std;

string arr[3];
map<pair<pair<string, string>, string>, bool> visited;

bool check(string a, string b, string c)
{
	int i;

	for (i = 0; i < a.length(); i++)
	{
		if (a[i] != 'A') return false;
	}
	for (i = 0; i < b.length(); i++)
	{
		if (b[i] != 'B') return false;
	}
	for (i = 0; i < c.length(); i++)
	{
		if (c[i] != 'C') return false;
	}

	return true;
}

int main()
{
	int i, j;
	int q;
	queue<pair<pair<string, string>, string>> que;
	string a, b, c;
	string na, nb, nc;
	int size;
	int d;

	for (i = 0; i < 3; i++)
	{
		cin >> q;
		if (q) cin >> arr[i];
	}

	d = 0;
	que.push(make_pair(make_pair(arr[0], arr[1]), arr[2]));
	visited[que.front()] = true;
	while (!que.empty())
	{
		size = que.size();
		while (size--)
		{
			arr[0] = que.front().first.first;
			arr[1] = que.front().first.second;
			arr[2] = que.front().second;
			que.pop();

			if (check(arr[0], arr[1], arr[2]))
			{
				cout << d;
				return 0;
			}

			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (i == j) continue;
					if (arr[i].empty()) continue;

					arr[j].push_back(arr[i].back());
					arr[i].pop_back();

					if (visited.find(make_pair(make_pair(arr[0], arr[1]), arr[2])) == visited.end())
					{
						visited[make_pair(make_pair(arr[0], arr[1]), arr[2])] = true;
						que.push(make_pair(make_pair(arr[0], arr[1]), arr[2]));
					}

					arr[i].push_back(arr[j].back());
					arr[j].pop_back();
				}
			}
		}
		d++;
	}
}
