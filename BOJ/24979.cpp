#include<iostream>
using namespace std;

string str;
int prefix[200010][3];

int main()
{
	int q;
	int i;
	int s, e;
	int a, b, c;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);

	cin >> str;

	str = '#' + str;

	for (i = 1; i < str.length(); i++)
	{
		prefix[i][0] = prefix[i - 1][0];
		prefix[i][1] = prefix[i - 1][1];
		prefix[i][2] = prefix[i - 1][2];

		if (str[i] == 'C') prefix[i][0]++;
		else if (str[i] == 'O') prefix[i][1]++;
		else prefix[i][2]++;
	}

	cin >> q;
	while (q--)
	{
		cin >> s >> e;

		a = prefix[e][0] - prefix[s - 1][0];
		b = prefix[e][1] - prefix[s - 1][1];
		c = prefix[e][2] - prefix[s - 1][2];

		a %= 2;
		b %= 2;
		c %= 2;

		if (a == 1 && b == 0 && c == 0) cout << 'Y';
		else if (a == 0 && b == 1 && c == 1) cout << 'Y';
		else cout << 'N';
	}
}
