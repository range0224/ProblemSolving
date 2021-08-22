#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int n;
vector<int> v;
int arr[30];
multiset<int> ms;
bool flag;

void recur(int cur)
{
	int i;
	int idx;

	if (flag) return;

	if (cur == n)
	{
		sort(arr, arr + n);

		for (i = 0; i < n; i++)
		{
			cout << arr[i] << ' ';
		}
		flag = true;

		return;
	}

	arr[cur] = *(--ms.end());
	for (i = 0; i < cur; i++)
	{
		if (ms.find(abs(arr[cur] - arr[i])) == ms.end()) break;

		ms.erase(ms.find(abs(arr[cur] - arr[i])));
	}
	idx = i;

	if (idx == cur) recur(cur + 1);

	for (i = 0; i < idx; i++)
	{
		ms.insert(abs(arr[cur] - arr[i]));
	}

	arr[cur] = arr[1] - *(--ms.end());
	for (i = 0; i < cur; i++)
	{
		if (ms.find(abs(arr[cur] - arr[i])) == ms.end()) break;

		ms.erase(ms.find(abs(arr[cur] - arr[i])));
	}
	idx = i;

	if (idx == cur) recur(cur + 1);

	for (i = 0; i < idx; i++)
	{
		ms.insert(abs(arr[cur] - arr[i]));
	}
}

int main()
{
	int i;
	int x;

	cin >> n;
	for (i = 0; i < n * (n - 1) / 2; i++)
	{
		cin >> x;

		v.push_back(x);
		ms.insert(x);
	}

	sort(v.begin(), v.end());

	arr[0] = 0;
	arr[1] = v[v.size() - 1];
	ms.erase(ms.find(arr[1]));
	recur(2);
}
