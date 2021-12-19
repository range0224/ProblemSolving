#include<iostream>
#include<string>
using namespace std;

int n, m;
string str;
bool visited[20010];

int main()
{
	int i, j;
	int cnt;

	cin >> n >> m;
	cin >> str;

	cnt = 0;
	for (i = 0; i < n; i++)
	{
		if (str[i] == 'H')
		{
			for (j = i - m; j <= i + m; j++)
			{
				if (j < 0 || j >= n) continue;

				if (str[j] == 'P' && !visited[j])
				{
					visited[j] = true;
					cnt++;
					break;
				}
			}
		}
	}

	cout << cnt;
}
