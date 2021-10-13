#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string str;
string num[10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR" ,"FIVE" ,"SIX" ,"SEVEN", "EIGHT", "NINE"};
int cnt[26];
int order[10] = { 0, 2, 6, 7, 5, 8, 4, 3, 1, 9 };
int number[10];

int main()
{
	int t, T;
	int i, j;
	int x;
	int mn;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> T;
	for (t = 1; t <= T; t++)
	{
		cin >> str;

		for (i = 0; i < 26; i++) cnt[i] = 0;

		for (i = 0; i < str.length(); i++) cnt[str[i] - 'A']++;

		for (i = 0; i < 10; i++) number[i] = 0;

		for (i = 0; i < 10; i++)
		{
			x = order[i];
			mn = 100000;
			for (j = 0; j < num[x].size(); j++)
			{
				mn = min(mn, cnt[num[x][j] - 'A']);
			}

			number[x] = mn;
			for (j = 0; j < num[x].size(); j++) cnt[num[x][j] - 'A'] -= mn;
		}

		cout << "Case #" << t << ": ";
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < number[i]; j++)
			{
				cout << i;
			}
		}
		cout << '\n';
	}
}
