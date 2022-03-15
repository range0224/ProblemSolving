#include<iostream>
using namespace std;

int n;
int a[100010];
int b[100010];
int pos[100010];
bool visited[100010];

int main()
{
    int i;
    int idx;
    int cnt;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> a[i];
        
        pos[a[i]] = i;
    }
    for(i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    
    idx = 0;
    cnt = 0;
    for(i = 0; i < n; i++)
    {
        if(a[idx] == b[i])
        {
            visited[idx] = true;
            while(visited[idx]) idx++;
            
            continue;
        }
        
        visited[pos[b[i]]] = true;
        cnt++;
    }
    
    cout << cnt;
}
