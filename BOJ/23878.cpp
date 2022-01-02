#include<iostream>
#include<string>
using namespace std;

int n;
string str;
int prv[500010];
int nxt[500010];

int main()
{
	int i;
	int idx1, idx2;
	long long cnt;
	long long a, b;

	cin >> n;
	cin >> str;

	idx1 = -1;
	idx2 = -1;
	for (i = 0; i < n; i++)
	{
		if (str[i] == 'G')
		{
			prv[i] = idx1;
			idx1 = i;
		}
		else
		{
			prv[i] = idx2;
			idx2 = i;
		}
	}

	idx1 = n;
	idx2 = n;
	for (i = n - 1; i >= 0; i--)
	{
		if (str[i] == 'G')
		{
			nxt[i] = idx1;
			idx1 = i;
		}
		else
		{
			nxt[i] = idx2;
			idx2 = i;
		}
	}

	cnt = 0;
	for (i = 0; i < n; i++)
	{
		a = i - prv[i] - 1;
		b = nxt[i] - i - 1;

		cnt += (a + 1) * (b + 1);

		if (a != 0 && b != 0) cnt -= 3;
		else if (a != 0) cnt -= 2;
		else if (b != 0) cnt -= 2;
		else cnt--;
	}

	cout << cnt;
}
