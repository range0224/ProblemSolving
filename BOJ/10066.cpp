#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

typedef struct node_t
{
    int len;
    int link;
    map<char, int> nxt;
}node;

string str;
int cnt = 2;
int last = 2;
node tree[300010];
int cnt2[300010];

void make_node(char c, int idx)
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
        cnt2[last]++;
        return;
    }
    
    nxt = last = tree[cur].nxt[c] = ++cnt;
    tree[nxt].len = tree[cur].len + 2;
    cnt2[cnt]++;
    
    if(tree[nxt].len == 1)
    {
        tree[nxt].link = 2;
        return;
    }
    
    while(cur > 1)
    {
        cur = tree[cur].link;
        if(idx - tree[cur].len - 1 >= 0 && str[idx - tree[cur].len - 1] == c)
        {
            tree[nxt].link = tree[cur].nxt[c];
            break;
        }
    }
}

int main()
{
    int i;
    long long ans;
    
    cin >> str;
    
    tree[1].len = -1;
    tree[1].link = 1;
    tree[2].len = 0;
    tree[2].link = 1;

    for(i = 0; i < str.length(); i++)
    {
        make_node(str[i], i);
    }
    
    ans = 0;
    for(i = cnt; i > 2; i--)
    {
        ans = max(ans, 1LL * tree[i].len * cnt2[i]);
        cnt2[tree[i].link] += cnt2[i];
    }
    
    cout << ans;
}
