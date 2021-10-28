#include<iostream>
using namespace std;

const int SIZE = 1 << 18;
const int len = 1 << 17;
int n;
int arr[100010];
int idx[100010];
int tree[SIZE];

void update(int idx, int value)
{
    idx += len;
    while(idx >= 1)
    {
        tree[idx] += value;
        idx /= 2;
    }
}

int get(int idx, int s, int e, int ts, int te)
{
    int mid;
    
    if(s > te || e < ts) return 0;
    else if(ts <= s && e <= te) return tree[idx];
    
    mid = (s + e) / 2;
    
    return get(2 * idx, s, mid, ts, te) + get(2 * idx + 1, mid + 1, e, ts, te);
}

int main()
{
    int t;
    int i;
    int x;
    long long ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(i = 0; i < n; i++)
        {
            cin >> x;
            
            idx[x] = i;
        }
        for(i = 0; i < n; i++)
        {
            cin >> x;
            
            arr[i] = idx[x];
        }
        
        ans = 0;
        for(i = 0; i < n; i++)
        {
            ans += get(1, 0, len - 1, arr[i], n);
            update(arr[i], 1);
        }
        
        cout << ans << '\n';
        
        for(i = 0; i < n; i++)
        {
            update(arr[i], -1);
        }
    }
}
