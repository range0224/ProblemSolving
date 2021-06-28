#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

string str;
stack<pair<int, int>> st;
vector<pair<int, int>> ans;

int main()
{
	int x;
	int i;
	int cnt = 1;
	int cur;
	int temp;
	int idx;
	int s = 1;
	int cur_idx = 1;

	cin.tie(NULL);
	ios::sync_with_stdio(false);

	cin >> str;
	str += '#';
	for (i = 1; i < str.length(); i++)
	{
		if (str[i] != str[i - 1])
		{
			if (st.size() >= 2)
			{
				cur = st.top().first;
				idx = st.top().second;
				st.pop();

				if (cnt >= cur)
				{
					ans.push_back(make_pair(idx, cur_idx - (cnt - cur)));
					cur_idx -= cur_idx - (cnt - cur) - idx + 1;
					temp = st.top().first + cnt - cur;
					idx = st.top().second;
					st.pop();
					st.push(make_pair(temp, idx));

					s = cur_idx + 1;
					cnt = 1;
				}
				else
				{
					ans.push_back(make_pair(idx + cur - cnt, cur_idx));
					cur_idx -= cur_idx - (idx + cur - cnt) + 1;
					s = idx;
					cnt = cur - cnt + 1;
				}
			}
			else
			{
				st.push(make_pair(cnt, s));
				s = cur_idx + 1;
				cnt = 1;
			}
		}
		else cnt++;
		cur_idx++;
	}
	ans.push_back(make_pair(1, cur_idx - 1));

	cout << ans.size() << '\n';
	for (i = 0; i < ans.size(); i++)
	{
		cout << ans[i].first << ' ' << ans[i].second << '\n';
	}
}
