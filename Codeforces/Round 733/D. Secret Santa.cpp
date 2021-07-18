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
int arr[200010];
int ans[200010];
bool visited[200010];
int pos[200010];
vector<int> v;
 
int main()
{
	int t;
	int i;
	int idx;
	int cnt;
	int temp;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		for (i = 1; i <= n; i++) visited[i] = false;
 
		for (i = 0; i < n; i++)
		{
			visited[arr[i]] = true;
		}
 
		v.clear();
		for (i = 1; i <= n; i++)
		{
			if (!visited[i]) v.push_back(i);
		}
 
		for (i = 1; i <= n; i++) visited[i] = false;
 
		idx = 0;
		for (i = 0; i < n; i++)
		{
			if (!visited[arr[i]])
			{
				ans[i] = arr[i];
				pos[arr[i]] = i;
				visited[arr[i]] = true;
			}
			else
			{
				ans[i] = v[idx];
				pos[v[idx]] = i;
				idx++;
			}
		}
 
		for (i = 0; i < n; i++)
		{
			if (ans[i] == i + 1)
			{
				idx = pos[arr[i]];
 
				swap(pos[arr[i]], pos[ans[i]]);
				swap(ans[idx], ans[i]);
			}
		}
 
		cnt = 0;
		for (i = 0; i < n; i++)
		{
			if (ans[i] == arr[i]) cnt++;
		}
 
		cout << cnt << '\n';
		for (i = 0; i < n; i++)
		{
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}
}
