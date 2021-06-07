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
 
int n;
int arr[200010];
set<int> st;
 
int main()
{
	int t;
	int i;
	bool flag;
	int idx;
 
	cin >> t;
	while (t--)
	{
		cin >> n;
 
		for (i = 0; i < n; i++)
		{
			cin >> arr[i];
		}
 
		flag = true;
		st.clear();
		st.insert(arr[0]);
		auto it = st.begin();
		for (i = 1; i < n; i++)
		{
			if (*it < arr[i])
			{
				it++;
				if (it == st.end())
				{
					st.insert(arr[i]);
					it--;
				}
				else if (*it > arr[i])
				{
					st.insert(arr[i]);
					it--;
				}
 
				if (*it != arr[i])
				{
					flag = false;
					break;
				}
			}
			else if (*it > arr[i])
			{
				if (it == st.begin())
				{
					st.insert(arr[i]);
					it--;
				}
				else it--;
 
				if (*it < arr[i])
				{
					st.insert(arr[i]);
					it++;
				}
 
				if (*it != arr[i])
				{
					flag = false;
					break;
				}
			}
		}
 
		if (flag) cout << "YES\n";
		else cout << "NO\n";
	}
}
