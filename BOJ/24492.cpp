#include<iostream>
#include<stack>
using namespace std;

int n;
int arr[300010];

int main()
{
	int i;
	stack<int> st;
	long long ans;

	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> arr[i];
	}

	ans = 0;
	for (i = 1; i <= n; i++)
	{
		while (!st.empty() && arr[st.top()] < arr[i])
		{
			ans += i - st.top() + 1;
			st.pop();
		}

		if (!st.empty()) ans += i - st.top() + 1;

		st.push(i);
	}

	cout << ans;
}
