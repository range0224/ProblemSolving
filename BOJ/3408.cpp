#include<iostream>
#include<map>
using namespace std;

int n;
int arr[200010];
int prv[200010], nxt[200010], idx[200010];
map<int, int> m;

bool recur(int s, int e)
{
	int l, r;

	if (s >= e) return true;

	l = s;
	r = e;
	while (l <= r)
	{
		if (prv[l] < s && nxt[l] > e) return recur(s, l - 1) && recur(l + 1, e);
		if (prv[r] < s && nxt[r] > e) return recur(s, r - 1) && recur(r + 1, e);
		l++;
		r--;
	}

	return false;
}

int main()
{
	int t;
	int i;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> t;
	while (t--)
	{
		m.clear();

		cin >> n;
		for (i = 1; i <= n; i++)
		{
			cin >> arr[i];

			if (m.find(arr[i]) == m.end()) m[arr[i]] = m.size() + 1;

			prv[i] = 0;
			nxt[i] = 0;
			idx[i] = 0;
		}

		for (i = 1; i <= n; i++)
		{
			prv[i] = idx[m[arr[i]]];
			nxt[idx[m[arr[i]]]] = i;
			nxt[i] = n + 1;
			idx[m[arr[i]]] = i;
		}

		if (recur(1, n)) cout << "non-boring\n";
		else cout << "boring\n";
	}
}
