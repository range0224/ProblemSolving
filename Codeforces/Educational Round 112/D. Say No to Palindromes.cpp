#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;
 
const int SQRT = 400;
int n;
string str;
vector<pair<pair<int, int>, int>> v;
int ans[200010];
int answer[6];
string pattern[6] = {"abc", "acb", "bac", "bca", "cab", "cba"};
 
bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
	if (a.first.first / SQRT != b.first.first / SQRT) return a.first.first < b.first.first;
	else return a.first.second < b.first.second;
}
 
void add_front_query(char x)
{
	int i;
	int temp[6];
 
	temp[0] = answer[3];
	temp[1] = answer[5];
	temp[2] = answer[1];
	temp[3] = answer[4];
	temp[4] = answer[0];
	temp[5] = answer[2];
 
	for (i = 0; i < 6; i++) answer[i] = temp[i];
 
	for (i = 0; i < 6; i++)
	{
		if (pattern[i][0] != x) answer[i]++;
	}
}
 
void add_back_query(int idx, char x)
{
	int i;
 
	for (i = 0; i < 6; i++)
	{
		if (pattern[i][idx] != x) answer[i]++;
	}
}
 
void delete_front_query(char x)
{
	int i;
	int temp[6];
 
	for (i = 0; i < 6; i++)
	{
		if (pattern[i][0] != x) answer[i]--;
	}
 
	temp[3] = answer[0];
	temp[5] = answer[1];
	temp[1] = answer[2];
	temp[4] = answer[3];
	temp[0] = answer[4];
	temp[2] = answer[5];
 
	for (i = 0; i < 6; i++) answer[i] = temp[i];
}
 
void delete_back_query(int idx, char x)
{
	int i;
 
	for (i = 0; i < 6; i++)
	{
		if (pattern[i][idx] != x) answer[i]--;
	}
}
 
int get_ans()
{
	int i;
	int ret = 1000000;
 
	for (i = 0; i < 6; i++)
	{
		ret = min(ret, answer[i]);
	}
 
	return ret;
}
 
int main()
{
	int q;
	int i;
	int a, b;
 
	cin.tie(NULL);
	ios::sync_with_stdio(false);
 
	cin >> n >> q;
	cin >> str;
	for (i = 0; i < q; i++)
	{
		cin >> a >> b;
 
		v.push_back(make_pair(make_pair(a - 1, b - 1), i));
	}
 
	sort(v.begin(), v.end(), comp);
 
	a = v[0].first.first;
	b = v[0].first.second;
	for (i = a; i <= b; i++)
	{
		add_back_query((i - a) % 3, str[i]);
	}
 
	ans[v[0].second] = get_ans();
 
	for (i = 1; i < q; i++)
	{
		while (a > v[i].first.first)
		{
			a--;
 
			add_front_query(str[a]);
		}
		while (b < v[i].first.second)
		{
			b++;
 
			add_back_query((b - a) % 3, str[b]);
		}
		while (a < v[i].first.first)
		{
			delete_front_query(str[a]);
 
			a++;
		}
		while (b > v[i].first.second)
		{
			delete_back_query((b - a) % 3, str[b]);
 
			b--;
		}
 
		ans[v[i].second] = get_ans();
	}
 
	for (i = 0; i < q; i++)
	{
		cout << ans[i] << '\n';
	}
}
