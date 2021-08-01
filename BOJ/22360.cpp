#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<algorithm>
#include<cstring>
using namespace std;

int n;
string str;
vector<int> v[200010];
int tree_size[200010];
bool visited[200010];
map<int, int> mp[4][400010];
long long ans;

int get_size(int cur)
{
    int i;
    int ret = 1;

    visited[cur] = true;
    for (i = 0; i < v[cur].size(); i++)
    {
        if (visited[v[cur][i]]) continue;

        ret += get_size(v[cur][i]);
    }
    visited[cur] = false;

    return tree_size[cur] = ret;
}

int get_centroid(int cur, int prev, int size)
{
    int i;

    for (i = 0; i < v[cur].size(); i++)
    {
        if (v[cur][i] == prev) continue;

        if (!visited[v[cur][i]] && 2 * tree_size[v[cur][i]] > size) return get_centroid(v[cur][i], cur, size);
    }

    return cur;
}

void get_ans(int cur, int gap, int gap2, int depth)
{
    int i;

    if(str[cur] == 'C') gap++;
    else gap--;
    
    if(str[cur] == 'U') gap2++;
    else if(str[cur] == 'P') gap2--;
    
    if(mp[3 - depth][200000 - gap2].find(-gap) != mp[3 - depth][200000 - gap2].end()) ans += mp[3 - depth][200000 - gap2][-gap];

    visited[cur] = true;
    for (i = 0; i < v[cur].size(); i++)
    {
        if (visited[v[cur][i]]) continue;

        get_ans(v[cur][i], gap, gap2, (depth + 1) % 4);
    }
    visited[cur] = false;
}

void get_dist(int cur, int gap, int gap2, int depth)
{
    int i;
    
    if(str[cur] == 'C') gap++;
    else gap--;
    
    if(str[cur] == 'U') gap2++;
    else if(str[cur] == 'P') gap2--;

    if(mp[depth][200000 + gap2].find(gap) == mp[depth][200000 + gap2].end()) mp[depth][200000 + gap2][gap] = 1;
    else mp[depth][200000 + gap2][gap]++;

    visited[cur] = true;
    for (i = 0; i < v[cur].size(); i++)
    {
        if (visited[v[cur][i]]) continue;

        get_dist(v[cur][i], gap, gap2, (depth + 1) % 4);
    }
    visited[cur] = false;
}

void recur(int cur)
{
    int centroid;
    int i, j;
    int gap, gap2;

    get_size(cur);
    centroid = get_centroid(cur, -1, tree_size[cur]);

    visited[centroid] = true;
    for(i = 0; i < 4; i++)
    {
        for(j = 200000 - tree_size[cur]; j <= 200000 + tree_size[cur]; j++)
        {
            mp[i][j].clear();
        }
    }
    if(str[centroid] == 'C') gap = 1;
    else gap = -1;
    
    if(str[centroid] == 'U') gap2 = 1;
    else if(str[centroid] == 'P') gap2 = -1;
    else gap2 = 0;
    
    mp[0][200000 + gap2][0] = 1;
    for (i = 0; i < v[centroid].size(); i++)
    {
        if (visited[v[centroid][i]]) continue;

        get_ans(v[centroid][i], gap, 0, 1);
        get_dist(v[centroid][i], 0, gap2, 1);
    }

    for (i = 0; i < v[centroid].size(); i++)
    {
        if (visited[v[centroid][i]]) continue;

        recur(v[centroid][i]);
    }
}

int main()
{
    int i;
    int a, b;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n;
    cin >> str;
    for(i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        
        v[a].push_back(b);
        v[b].push_back(a);
    }
    
    str = '#' + str;
    
    recur(1);
    
    cout << ans;
}
