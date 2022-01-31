#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int a, b;
int dif;
bool flag;
int arr2[10010];

int partition(int arr[], int s, int e)
{
    int x;
    int i, j;
    int idx;
    
    x = arr[e];
    i = s - 1;
    for(j = s; j < e; j++)
    {
        if(arr[j] <= x)
        {
            swap(arr[++i], arr[j]);
            
            if(i != j)
            {
                if(arr[i] == arr2[i]) dif--;
                if(arr[i] == arr2[j]) dif++;
                if(arr[j] == arr2[i]) dif++;
                if(arr[j] == arr2[j]) dif--;
                
                if(!dif) flag = true;
            }
        }
    }
    if(i + 1 != e)
    {
        swap(arr[i + 1], arr[e]);
    
        if(arr[i + 1] == arr2[i + 1]) dif--;
        if(arr[i + 1] == arr2[e]) dif++;
        if(arr[e] == arr2[i + 1]) dif++;
        if(arr[e] == arr2[e]) dif--;
        
        if(!dif) flag = true;
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
    int arr[10010];
    int i;
    
    cin >> n >> m;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for(i = 0; i < n; i++)
    {
        cin >> arr2[i];
    }
    
    for(i = 0; i < n; i++)
    {
        if(arr[i] != arr2[i]) dif++;
    }
    
    if(!dif) flag = true;
    
    select(arr, 0, n - 1, m);
    
    if(flag) cout << 1;
    else cout << 0;
}
