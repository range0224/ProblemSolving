#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;

int n, m;
vector<string> color;
vector<string> name;
bool mat[2020];

string rev(string s)
{
	string ret;
	int i;

	for (i = s.length() - 1; i >= 0; i--) ret += s[i];

	return ret;
}

int main()
{
	int q;
	int i;
	string str, str2;
	int s, e;
	int idx;
	bool flag;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> n >> m;
	for (i = 0; i < n; i++)
	{
		cin >> str;

		color.push_back(str);
	}
	for (i = 0; i < m; i++)
	{
		cin >> str;

		name.push_back(rev(str));
	}

	sort(color.begin(), color.end());
	sort(name.begin(), name.end());

	cin >> q;
	while (q--)
	{
		cin >> str;

		memset(mat, false, sizeof(mat));

		flag = false;

		s = 0;
		e = color.size() - 1;
		for (i = 0; i < str.length(); i++)
		{
			while (s <= e && !(color[s].length() > i && color[s][i] == str[i])) s++;
			while (s <= e && !(color[e].length() > i && color[e][i] == str[i])) e--;

			mat[i] = (s <= e && color[s].length() == i + 1);
		}

		s = 0;
		e = name.size() - 1;
		for (i = str.length() - 1; i > 0; i--)
		{
			idx = str.length() - i - 1;
			while (s <= e && !(name[s].length() > idx && name[s][idx] == str[i])) s++;
			while (s <= e && !(name[e].length() > idx && name[e][idx] == str[i])) e--;

			if (s <= e && name[s].length() == idx + 1 && mat[i - 1]) flag = true;
		}

		if (flag) cout << "Yes\n";
		else cout << "No\n";
	}
}
