#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
using namespace std;
 
int n, m;
vector<pair<int, int>> v;
int pos[300010];
int arr[300010];
int ans[300010];
 
int main()
{
	int t;
	int i;
	stack<int> st;
	int idx;
 
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		for (i = 0; i < m; i++)
		{
			cin >> pos[i];
		}
		for (i = 0; i < m; i++)
		{
			cin >> arr[i];
		}
 
		v.clear();
		for (i = 0; i < m; i++)
		{
			v.push_back(make_pair(pos[i], arr[i]));
		}
 
		v.push_back(make_pair(0, 2000000000));
		v.push_back(make_pair(n + 1, 2000000000));
		sort(v.begin(), v.end());
 
		while (!st.empty()) st.pop();
 
		st.push(0);
		idx = 1;
		for (i = 1; i <= n; i++)
		{
			if (idx < v.size() && v[idx].first == i)
			{
				if (v[st.top()].second + (i - v[st.top()].first) > v[idx].second) st.push(idx);
				idx++;
			}
 
			ans[i] = v[st.top()].second + (i - v[st.top()].first);
		}
 
		while (!st.empty()) st.pop();
		
		st.push(v.size() - 1);
		idx = v.size() - 2;
		for (i = n; i >= 1; i--)
		{
			if (idx >= 0 && v[idx].first == i)
			{
				if (v[st.top()].second + (v[st.top()].first - i) > v[idx].second) st.push(idx);
				idx--;
			}
 
			ans[i] = min(ans[i], v[st.top()].second + (v[st.top()].first - i));
		}
 
		for (i = 1; i <= n; i++)
		{
			cout << ans[i] << ' ';
		}
		cout << '\n';
	}
}
