#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;

typedef struct node_t
{
    int value;
    node_t *l;
    node_t *r;
}node;

const int len = 1 << 18;
int n, m;
int arr[250010];
long long prefix[250010];
map<long long, int> mp;
long long rmp[250010];
int kth[250010];
node tree[250010];
priority_queue<pair<long long, int>> pq;

void make_tree(node& root, int s, int e)
{
    int mid;
    
    root.value = 0;
    
    if(s == e) return;
    
    mid = (s + e) / 2;
    
    root.l = new node();
    root.r = new node();
    make_tree(*root.l, s, mid);
    make_tree(*root.r, mid + 1, e);
}

void update(node& prv, node& root, int s, int e, int idx, int value)
{
    int mid;
    
    if(s == e)
    {
        root.value += value;
        
        return;
    }
    
    mid = (s + e) / 2;
    
    if(idx <= mid)
    {
        root.l = new node();
        root.r = prv.r;
        root.l->value = prv.l->value;
        update(*prv.l, *root.l, s, mid, idx, value);
    }
    else
    {
        root.l = prv.l;
        root.r = new node();
        root.r->value = prv.r->value;
        update(*prv.r, *root.r, mid + 1, e, idx, value);
    }
    
    root.value = root.l->value + root.r->value;
}

int get(node& prv, node& root, int s, int e, int &k)
{
    int mid;
    
    if(s == e) return s;
    
    mid = (s + e) / 2;
    
    if(root.l->value - prv.l->value >= k) return get(*prv.l, *root.l, s, mid, k);
    else
    {
        k -= root.l->value - prv.l->value;
        return get(*prv.r, *root.r, mid + 1, e, k);
    }
}

int main()
{
    int i;
    int x;
    vector<long long> tv;
    int idx;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> m;
    for(i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    
    for(i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
        
        tv.push_back(prefix[i]);
    }
    tv.push_back(0);
    
    sort(tv.begin(), tv.end());
    
    x = 2;
    mp[tv[0]] = 1;
    rmp[1] = tv[0];
    for(i = 1; i < tv.size(); i++)
    {
        if(tv[i] != tv[i - 1])
        {
            rmp[x] = tv[i];
            mp[tv[i]] = x;
            x++;
        }
    }
    
    for(i = 0; i <= n; i++)
    {
        prefix[i] = mp[prefix[i]];
    }
    
    make_tree(tree[0], 0, len - 1);
    for(i = 0; i <= n; i++)
    {
        update(tree[i], tree[i + 1], 0, len - 1, prefix[i], 1);
    }
    
    for(i = 1; i <= n; i++)
    {
        kth[i] = 1;
        x = kth[i];
        pq.push(make_pair(rmp[prefix[i]] - rmp[get(tree[0], tree[i], 0, len - 1, x)], i));
    }
    
    while(m--)
    {
        cout << pq.top().first << ' ';
        
        idx = pq.top().second;
        pq.pop();
        
        if(kth[idx] == idx) continue;
        
        kth[idx]++;
        x = kth[idx];
        pq.push(make_pair(rmp[prefix[idx]] - rmp[get(tree[0], tree[idx], 0, len - 1, x)], idx));
    }
}
