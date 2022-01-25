#include<iostream>
#include<algorithm>
using namespace std;

int k;
int a, b;
int cnt;

int partition(int arr[], int s, int e)
{
    int x;
    int i, j;
    
    x = arr[e];
    i = s - 1;
    for(j = s; j < e; j++)
    {
        if(arr[j] <= x)
        {
            cnt++;
            if(cnt == k)
            {
                a = arr[i + 1];
                b = arr[j];
            }
            swap(arr[++i], arr[j]);
        }
    }
    if(i + 1 != e)
    {
        cnt++;
        if(cnt == k)
        {
            a = arr[i + 1];
            b = arr[e];
        }
        swap(arr[i + 1], arr[e]);
    }
    
    return i + 1;
}

int select(int arr[], int s, int e, int m)
{
    int t;
    int x;
    
    if(s == e) return arr[s];
    
    t = partition(arr, s, e);
    x = t - s + 1;
    if(m < x) return select(arr, s, t - 1, m);
    else if(m == x) return arr[t];
    else return select(arr, t + 1, e, m - x);
}

int main()
{
    int n, m;
    int arr[10010];
    int i;
    
    cin >> n >> m >> k;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    select(arr, 0, n - 1, m);
    
    if(cnt < k) cout << -1;
    else cout << min(a, b) << ' ' << max(a, b);
}
