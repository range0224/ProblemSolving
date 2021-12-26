#include<iostream>
#include<map>
using namespace std;

int n, m;
int arr[15];
map<int, bool> visited;
bool used[15];
int ans;

int get_len(int x)
{
	int ret = 1;

	while (x)
	{
		ret *= 10;
		x /= 10;
	}

	return ret;
}

void recur(int cnt, int num)
{
	int i;

	if (cnt == m)
	{
		if(visited.find(num) == visited.end()) ans++;
		visited[num] = true;

		return;
	}

	for (i = 0; i < n; i++)
	{
		if (used[i]) continue;

		used[i] = true;
		recur(cnt + 1, num * get_len(arr[i]) + arr[i]);
		used[i] = false;
	}
}

int main()
{
	int i;

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	recur(0, 0);

	cout << ans;
}
