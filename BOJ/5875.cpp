#include<iostream>
using namespace std;

int arr[100010];
bool prefix[100010];
bool suffix[100010];

int main()
{
    string s;
    int i;
    int cnt;
    
    cin >> s;
    
    if(s.length() % 2 == 1)
    {
        cout << 0;
        
        return 0;
    }
    
    s = "#" + s;
    
    for(i = 1; i < s.length(); i++)
    {
        arr[i] = arr[i - 1];
        
        if(s[i] == '(') arr[i]++;
        else arr[i]--;
    }
    
    for(i = 1; i < s.length(); i++)
    {
        prefix[i] = prefix[i - 1];
        if(arr[i] < 0) prefix[i] = true;
    }
    
    for(i = (int)s.length() - 1; i >= 1; i--)
    {
        suffix[i] = suffix[i + 1];
        if(arr[i] < 2) suffix[i] = true;
    }
    
    cnt = 0;
    for(i = 1; i < s.length(); i++)
    {
        if(s[i] == '(' && !prefix[i] && !suffix[i] && arr[s.length() - 1] - 2 == 0) cnt++;
        if(s[i] == ')' && !prefix[i - 1] && arr[i] + 2 >= 0 && arr[s.length() - 1] + 2 == 0) cnt++;
    }
    
    cout << cnt;
}
