#include<iostream>
#include<string>
using namespace std;

int main()
{
    string str;
    int i;
    int sum;
    int cnt;
    
    cin >> str;
    
    sum = 0;
    for(i = 0; i < str.length(); i++)
    {
        if(str[i] == '(') sum++;
        else sum--;
    }
    
    cnt = 0;
    if(sum > 0)
    {
        sum = 0;
        for(i = 0; i < str.length(); i++)
        {
            if(str[i] == '(')
            {
                sum++;
                cnt++;
            }
            else sum--;
            
            if(sum == 0) cnt = 0;
        }
    }
    else
    {
        sum = 0;
        for(i = 0; i < str.length(); i++)
        {
            if(str[i] == '(') sum++;
            else
            {
                sum--;
                cnt++;
            }
            
            if(sum < 0) break;
        }
    }
    
    cout << cnt;
}
