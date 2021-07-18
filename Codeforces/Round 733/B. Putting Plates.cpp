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
int arr[30][30];
int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };
 
int main()
{
	int t;
	int i, j, k;
	int nx, ny;
	bool flag;
 
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
 
		for (i = 0; i <= n + 1; i++)
		{
			for (j = 0; j <= m + 1; j++)
			{
				arr[i][j] = 0;
			}
		}
 
		arr[1][1] = 1;
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= m; j++)
			{
				if (i != 1 && i != n && j != 1 && j != m) continue;
 
				flag = true;
				for (k = 0; k < 8; k++)
				{
					nx = i + dx[k];
					ny = j + dy[k];
 
					if (arr[nx][ny]) flag = false;
				}
 
				if (flag) arr[i][j] = 1;
			}
		}
 
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= m; j++)
			{
				cout << arr[i][j];
			}
			cout << '\n';
		}
		cout << '\n';
	}
}
