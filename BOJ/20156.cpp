#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;
int par[100010];
int arr[100010];
int arr2[100010];
int fin[100010];
int ans[100010];
bool visited[100010];
vector<pair<pair<int, int>, pair<int, int>>> v;

int find(int x)
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    par[a] = b;
}

int main()
{
    int i;
    int a, b, c;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m >> k;
    for(i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for(i = 0; i < m; i++)
    {
        cin >> arr2[i];
        
        if(visited[arr2[i]]) arr2[i] = 0;
        visited[arr2[i]] = true;
    }
    for(i = 0; i < k; i++)
    {
        cin >> a >> b >> c;
        
        v.push_back(make_pair(make_pair(a, i), make_pair(b, c)));
    }
    
    sort(v.begin(), v.end());
    
    for(i = 1; i <= n; i++)
    {
        fin[i] = arr[i];
    }
    for(i = 0; i < m; i++)
    {
        fin[arr2[i]] = -1;
    }
    
    for(i = 1; i <= n; i++) par[i] = i;
    
    for(i = 1; i <= n; i++)
    {
        if(fin[i] != -1) union_(i, fin[i]);
    }
    
    idx = m - 1;
    for(i = k - 1; i >= 0; i--)
    {
        while(v[i].first.first <= idx)
        {
            if(arr[arr2[idx]] != -1) union_(arr2[idx], arr[arr2[idx]]);
            idx--;
        }
        
        if(find(v[i].second.first) == find(v[i].second.second)) ans[v[i].first.second] = 1;
    }
    
    for(i = 0; i < k; i++)
    {
        if(ans[i]) cout << "Same Same;\n";
        else cout << "No;\n";
    }
}
