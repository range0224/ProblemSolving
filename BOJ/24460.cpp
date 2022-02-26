#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[1050][1050];

int recur(int x, int y, int size)
{
	int tarr[4];

	if (size == 1) return arr[x][y];

	tarr[0] = recur(x, y, size / 2);
	tarr[1] = recur(x, y + size / 2, size / 2);
	tarr[2] = recur(x + size / 2, y, size / 2);
	tarr[3] = recur(x + size / 2, y + size / 2, size / 2);

	sort(tarr, tarr + 4);

	return tarr[1];
}

int main()
{
	int i, j;

	cin >> n;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	cout << recur(0, 0, n);
}
