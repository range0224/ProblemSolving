#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int> v[100010];
int prv[100010];
int s, e;

void dfs(int cur)
{
    int i;
    
    for(i = 0; i < v[cur].size(); i++)
    {
        if(v[cur][i] == prv[cur]) continue;
        
        prv[v[cur][i]] = cur;
        dfs(v[cur][i]);
    }
}

int main()
{
    int i;
    int a, b;
    int cur;
    vector<int> tv;
    
    cin >> n >> s >> e;
    for(i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    dfs(s);
    
    cur = e;
    while(cur != s)
    {
        cur = prv[cur];
        tv.push_back(cur);
    }
    
    for(i = (int)tv.size() - 2; i >= 0; i -= 2)
    {
        if(v[tv[i]].size() != 2)
        {
            cout << "Second";
            return 0;
        }
    }
    
    cout << "First";
}
