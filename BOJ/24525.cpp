#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

string str;
map<int, int> idx;
int cnt[100010];

int main()
{
    int i;
    int sum;
    int ans = -1;
    
    cin >> str;
    
    str = "#" + str;
    
    idx[0] = 0;
    sum = 0;
    for(i = 1; i < str.length(); i++)
    {
        cnt[i] = cnt[i - 1] + (str[i] == 'S');
        
        if(str[i] == 'S') sum += 2;
        else if(str[i] == 'K') sum--;
        
        if(idx.find(sum) != idx.end())
        {
            if(cnt[i] != cnt[idx[sum]]) ans = max(ans, i - idx[sum]);
        }
        else idx[sum] = i;
    }
    
    cout << ans;
}
