#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

const int SQRT = 500;
int n, m;
vector<pair<pair<int, int>, int>> v;
stack<pair<int, bool>> st;
int query[100010][3];
int par[100010];
int sz[100010];
int rnk[100010];
int ans[100010];
int tmp[100010];
int cnt;

bool comp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.second > b.second;
}

bool comp2(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.first.second > b.first.second;
}

int find(int x)
{
    if(par[x] == x) return x;
    else return find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    if(a == b) return;
    
    cnt++;
    
    if(rnk[a] < rnk[b])
    {
        par[a] = b;
        sz[b] += sz[a];
        st.push(make_pair(a, false));
    }
    else if(rnk[a] > rnk[b])
    {
        par[b] = a;
        sz[a] += sz[b];
        st.push(make_pair(b, false));
    }
    else
    {
        par[a] = b;
        sz[b] += sz[a];
        rnk[b]++;
        st.push(make_pair(a, true));
    }
}

void roll_back()
{
    int x;
    bool y;
    
    x = st.top().first;
    y = st.top().second;
    st.pop();
    
    if(y) rnk[par[x]]--;
    
    sz[par[x]] -= sz[x];
    par[x] = x;
}

void run_query(int s, int e)
{
    int i, j;
    bool used[100010] = {false};
    vector<pair<pair<int, int>, int>> tv2;
    vector<pair<pair<int, int>, int>> q;
    int idx;
    
    for(i = 1; i <= n; i++)
    {
        par[i] = i;
        sz[i] = 1;
        rnk[i] = 0;
    }
    while(!st.empty()) st.pop();
    
    for(i = s; i <= e; i++)
    {
        if(query[i][0] == 1) used[query[i][1]] = true;
        else q.push_back(make_pair(make_pair(query[i][1], query[i][2]), i));
    }
    
    for(i = 1; i <= m; i++)
    {
        if(!used[i]) tv2.push_back(v[i]);
    }
    
    sort(q.begin(), q.end(), comp2);
    sort(tv2.begin(), tv2.end(), comp);
    
    idx = 0;
    for(i = 0; i < q.size(); i++)
    {
        while(idx < tv2.size() && tv2[idx].second >= q[i].first.second)
        {
            union_(tv2[idx].first.first, tv2[idx].first.second);
            idx++;
        }
        
        for(j = s; j < q[i].second; j++)
        {
            if(query[j][0] == 1)
            {
                tmp[j] = v[query[j][1]].second;
            }
        }
        for(j = s; j < q[i].second; j++)
        {
            if(query[j][0] == 1)
            {
                v[query[j][1]].second = query[j][2];
            }
        }
        cnt = 0;
        for(j = s; j <= e; j++)
        {
            if(query[j][0] == 1 && v[query[j][1]].second >= q[i].first.second)
            {
                union_(v[query[j][1]].first.first, v[query[j][1]].first.second);
            }
        }
        
        ans[q[i].second] = sz[find(q[i].first.first)];
        
        while(cnt--) roll_back();
        
        for(j = s; j < q[i].second; j++)
        {
            if(query[j][0] == 1)
            {
                v[query[j][1]].second = tmp[j];
            }
        }
    }
    
    for(i = s; i <= e; i++)
    {
        if(query[i][0] == 1)
        {
            v[query[i][1]].second = query[i][2];
        }
    }
}

int main()
{
    int q;
    int i, j;
    int a, b, c;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    v.push_back(make_pair(make_pair(0, 0), 0));
    
    cin >> n >> m;
    for(i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        
        v.push_back(make_pair(make_pair(a, b), c));
    }
    cin >> q;
    for(i = 0; i < q; i++)
    {
        for(j = 0; j < 3; j++)
        {
            cin >> query[i][j];
        }
    }
    
    for(i = 0; i < q; i += SQRT)
    {
        run_query(i, min(q, i + SQRT) - 1);
    }
    
    for(i = 0; i < q; i++)
    {
        if(query[i][0] == 2) cout << ans[i] << '\n';
    }
}
