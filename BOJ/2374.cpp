#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[1010];

long long recur(int s, int e)
{
	int i;
	int mx;
	int idx;
	long long ret;
	int mx2;

	if (s >= e) return 0;

	mx = -1;
	idx = 0;
	for (i = s; i <= e; i++)
	{
		if (mx < arr[i])
		{
			mx = arr[i];
			idx = i;
		}
	}

	ret = recur(s, idx - 1) + recur(idx + 1, e);

	if (s <= idx - 1)
	{
		mx2 = 0;
		for (i = s; i <= idx - 1; i++)
		{
			mx2 = max(mx2, arr[i]);
		}

		ret += mx - mx2;
	}
	if (idx + 1 <= e)
	{
		mx2 = 0;
		for (i = idx + 1; i <= e; i++)
		{
			mx2 = max(mx2, arr[i]);
		}

		ret += mx - mx2;
	}

	return ret;
}

int main()
{
	int i;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}

	cout << recur(0, n - 1);
}
