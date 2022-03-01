#include<iostream>
#include<stack>
using namespace std;

int n;
int ans[1000010];

int main()
{
    int i;
    int x;
    stack<pair<int, int>> st;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    for(i = 1; i <= n; i++)
    {
        cin >> x;
        
        while(!st.empty() && st.top().second != x)
        {
            ans[st.top().first] = i;
            st.pop();
        }
        
        st.push(make_pair(i, x));
    }
    
    while(!st.empty())
    {
        ans[st.top().first] = -1;
        st.pop();
    }
    
    for(i = 1; i <= n; i++)
    {
        cout << ans[i] << ' ';
    }
}
