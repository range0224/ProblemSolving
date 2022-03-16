#include<iostream>
#include<string>
using namespace std;

string str[4];
string s;
bool visited[4];
bool ans;

void recur(int cur)
{
    int i, j;
    bool flag;
    
    if(cur == s.length())
    {
        ans = true;
        return;
    }
    
    for(i = 0; i < 4; i++)
    {
        if(visited[i]) continue;
        
        flag = false;
        for(j = 0; j < 6; j++)
        {
            if(s[cur] == str[i][j])
            {
                flag = true;
                break;
            }
        }
        
        if(flag)
        {
            visited[i] = true;
            recur(cur + 1);
            visited[i] = false;
        }
    }
}

int main()
{
    int t;
    int i;
    
    cin >> t;
    for(i = 0; i < 4; i++)
    {
        cin >> str[i];
    }
    while(t--)
    {
        cin >> s;
        
        ans = false;
        recur(0);
        
        if(ans) cout << "YES\n";
        else cout << "NO\n";
    }
}
