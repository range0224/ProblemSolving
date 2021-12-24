#include<iostream>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
int tree[SIZE];

void update(int idx)
{
	idx += len;
	while (idx >= 1)
	{
		tree[idx]++;
		idx /= 2;
	}
}

int get(int idx, int s, int e, int ts, int te)
{
	int mid;

	if (s > te || e < ts) return 0;
	else if (ts <= s && e <= te) return tree[idx];
	
	mid = (s + e) / 2;

	return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
	int i;
	int x;
	int s, e;
	int mid;
	int idx;
	
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> x;

		s = 1;
		e = n;
		idx = 0;
		while (s <= e)
		{
			mid = (s + e) / 2;

			if (mid - get(1, 0, len - 1, 1, mid) - 1 >= x)
			{
				idx = mid;
				e = mid - 1;
			}
			else s = mid + 1;
		}

		arr[idx] = i;
		update(idx);
	}
	
	for (i = 1; i <= n; i++)
	{
		cout << arr[i] << '\n';
	}
}
