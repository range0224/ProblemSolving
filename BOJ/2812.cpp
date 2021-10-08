#include<iostream>
#include<string>
#include<stack>
using namespace std;

int n, m;
string str;

int main()
{
    int i;
    string ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    cin >> str;
    
    for(i = 0; i < str.length(); i++)
    {
        while(m > 0 && !ans.empty() && ans.back() < str[i])
        {
            ans.pop_back();
            m--;
        }
        ans.push_back(str[i]);
    }
    
    while(m--)
    {
        ans.pop_back();
    }
    
    cout << ans;
}
