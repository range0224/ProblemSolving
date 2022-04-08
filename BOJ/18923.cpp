#include<iostream>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

typedef struct node_t
{
    int len;
    int link;
    int link2;
    long long cnt;
    int cnt2;
    map<char, int> nxt;
}node;

long long recur2(int cur);

const int MOD = 998244353;
string str;
int cnt = 2;
int last = 2;
node tree[1000010];
long long dp[1000010];
long long dp2[1000010];

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
        tree[last].cnt2++;
        return;
    }

    nxt = last = tree[cur].nxt[c] = ++cnt;
    tree[nxt].link2 = cur;
    tree[nxt].len = tree[cur].len + 2;
    tree[nxt].cnt = tree[nxt].len - 1;
    tree[nxt].cnt2 = 1;

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
            break;
        }
    }
}

long long recur(int cur)
{
    long long ret;
    int x;
    
    if(cur <= 2) return 1;
    
    if(dp[cur] != -1) return dp[cur];
    
    ret = 2 * recur(tree[cur].link2);
    ret %= MOD;
    x = tree[cur].link;
    ret += recur2(x);
    ret %= MOD;
    
    return dp[cur] = ret;
}

long long recur2(int cur)
{
    if(cur <= 2) return 0;
    
    if(dp2[cur] != -1) return dp2[cur];
    
    return dp2[cur] = (2 * recur(tree[cur].link2) + recur2(tree[cur].link)) % MOD;
}

int main()
{
    int i;
    long long ans;

    cin >> str;

    tree[1] = {-1, 1, 0, 0, 0, map<char, int>()};
    tree[2] = {0, 1, 0, 0, 0, map<char, int>()};

    for(i = 0; i < str.length(); i++) make_node(str[i], i);

    for(i = cnt; i > 2; i--)
    {
        tree[tree[i].link].cnt2 += tree[i].cnt2;
    }
    
    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));

    ans = 0;
    for(i = 3; i <= cnt; i++)
    {
        tree[i].cnt = recur(tree[i].link2);

        ans += 1LL * tree[i].cnt * tree[i].cnt2;
        ans %= MOD;
    }

    cout << ans;
}
