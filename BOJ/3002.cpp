#include<iostream>
#include<string>
using namespace std;

const int SIZE = 1 << 19;
const int len = 1 << 18;
int n;
int tree[SIZE][10];
int lazy[SIZE];

void propagate(int idx, int s, int e)
{
    int i;
    int temp[10];
    
    if(idx < len)
    {
        lazy[2 * idx] += lazy[idx];
        lazy[2 * idx + 1] += lazy[idx];
    }
    
    for(i=0;i<10;i++)
    {
        temp[(i + lazy[idx]) % 10] = tree[idx][i];
    }
    for(i = 0; i < 10; i++)
    {
        tree[idx][i] = temp[i];
    }
    
    lazy[idx] = 0;
}

void update(int idx, int s, int e, int ts, int te)
{
    int mid;
    int i;
    
    propagate(idx, s, e);
    
    if(s > te || e < ts) return;
    else if(ts <= s && e <= te)
    {
        lazy[idx] = 1;
        propagate(idx, s, e);
        return;
    }
    
    mid = (s + e) / 2;
    
    update(2 * idx, s, mid, ts, te);
    update(2 * idx + 1, mid + 1, e, ts, te);
    
    for(i = 0; i < 10; i++)
    {
        tree[idx][i] = tree[2 * idx][i] + tree[2 * idx + 1][i];
    }
}

int get(int idx, int s, int e, int ts, int te)
{
    int mid;
    int i;
    int ret = 0;
    
    propagate(idx, s, e);
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te)
    {
        for(i = 0; i < 10; i++)
        {
            ret += i * tree[idx][i];
        }
        return ret;
    }
    
    mid = (s + e) / 2;
    
    return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
    int q;
    string str;
    int i, j;
    int a, b;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> n >> q;
    cin >> str;
    
    for(i = 1; i <= n; i++)
    {
        tree[i + len][str[i - 1] - '0'] = 1;
    }
    for(i = len - 1; i >= 1; i--)
    {
        for(j = 0; j < 10; j++)
        {
            tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
        }
    }
    
    while(q--)
    {
        cin >> a >> b;
        
        cout << get(1, 0, len - 1, a, b) << '\n';
        update(1, 0, len - 1, a, b);
    }
}
