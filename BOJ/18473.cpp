#include<iostream>
#include<queue>
using namespace std;

int n, m;
long long arr[300010];
int query[300010][3];
int par[300010];
int rnk[300010];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> *pq[300010];
priority_queue<int, vector<int>, greater<int>> pq2;
vector<int> ans;

int find(int x)
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    if(a == b) return;
    
    if(rnk[a] > rnk[b]) swap(a, b);
    
    par[a] = b;
    arr[b] += arr[a];
    rnk[b] += (rnk[a] == rnk[b]);
    if(pq[a]->size() > pq[b]->size()) swap(pq[a], pq[b]);
    while(!pq[a]->empty())
    {
        pq[b]->push(pq[a]->top());
        pq[a]->pop();
    }
}

void recur(int x)
{
    int a, b, c;
    
    x = find(x);
    while(!pq[x]->empty() && pq[x]->top().first <= arr[x])
    {
        pq2.push(pq[x]->top().second);
        pq[x]->pop();
    }
    
    while(!pq2.empty())
    {
        x = pq2.top();
        pq2.pop();
        
        a = find(query[x][0]);
        b = find(query[x][1]);
        c = query[x][2];
        
        if(a == b) continue;
        
        if(arr[a] + arr[b] >= c)
        {
            ans.push_back(x);
            union_(a, b);
            
            recur(a);
        }
        else
        {
            pq[a]->push(make_pair(arr[a] + (c - (arr[a] + arr[b]) + 1) / 2, x));
            pq[b]->push(make_pair(arr[b] + (c - (arr[a] + arr[b]) + 1) / 2, x));
        }
    }
}

int main()
{
    int i;
    int a, b, c;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for(i = 1; i <= m; i++)
    {
        cin >> query[i][0] >> query[i][1] >> query[i][2];
    }
    
    for(i = 1; i <= n; i++)
    {
        par[i] = i;
        pq[i] = new priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>();
    }
    
    for(i = 1; i <= m; i++)
    {
        a = find(query[i][0]);
        b = find(query[i][1]);
        c = query[i][2];
        
        if(a == b) continue;
        
        if(arr[a] + arr[b] >= c)
        {
            ans.push_back(i);
            union_(a, b);
            
            recur(a);
        }
        else
        {
            pq[a]->push(make_pair(arr[a] + (c - (arr[a] + arr[b]) + 1) / 2, i));
            pq[b]->push(make_pair(arr[b] + (c - (arr[a] + arr[b]) + 1) / 2, i));
        }
    }
    
    cout << ans.size() << '\n';
    for(i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << ' ';
    }
}
