#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

typedef struct node_t
{
    int len;
    int link;
    long long visit;
    map<char, int> nxt;
}node;

int n;
string str;
node tree[1000010];
int cnt = 2;
int last = 2;

void make_node(char c, int idx, int num)
{
    int cur = last;
    int nxt;
    
    while(1)
    {
        if(idx - tree[cur].len - 1 >= 0 && str[idx - tree[cur].len - 1] == c) break;
        cur = tree[cur].link;
    }
    
    if(tree[cur].nxt.find(c) != tree[cur].nxt.end())
    {
        last = tree[cur].nxt[c];
        tree[last].visit |= 1LL << num;
        return;
    }
    
    nxt = last = tree[cur].nxt[c] = ++cnt;
    tree[nxt].len = tree[cur].len + 2;
    tree[nxt].visit |= 1LL << num;
    
    if(tree[nxt].len == 1)
    {
        tree[nxt].link = 2;
        return;
    }
    
    while(1)
    {
        cur = tree[cur].link;
        if(idx - tree[cur].len - 1 >= 0 && str[idx - tree[cur].len - 1] == c)
        {
            tree[nxt].link = tree[cur].nxt[c];
            return;
        }
    }
}

int main()
{
    int i, j;
    int ans;
    
    tree[1] = {-1, 1, 0, map<char, int>()};
    tree[2] = {0, 1, 0, map<char, int>()};
    
    cin >> n;
    
    for(i = 0; i < n; i++)
    {
        cin >> str;
        
        last = 2;
        
        for(j = 0; j < str.length(); j++) make_node(str[j], j, i);
    }
    
    ans = 0;
    for(i = cnt; i > 2; i--)
    {
        if(tree[i].visit == ((1LL << n) - 1)) ans = max(ans, tree[i].len);
        
        tree[tree[i].link].visit |= tree[i].visit;
    }
    
    cout << ans;
}
