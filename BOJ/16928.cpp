#include<iostream>
#include<queue>
using namespace std;

int n, m;
int arr[110];
bool visited[110];

int main()
{
    int i;
    int a, b;
    int size;
    int cur;
    int nxt;
    int d;
    queue<int> que;
    
    for(i=1;i<=100;i++) arr[i] = i;
    
    cin >> n >> m;
    for(i = 0; i < n + m; i++)
    {
        cin >> a >> b;
        
        arr[a] = b;
    }
    
    d = 0;
    que.push(1);
    visited[1] = true;
    while(!que.empty())
    {
        size = que.size();
        while(size--)
        {
            cur = que.front();
            que.pop();
            
            if(cur == 100)
            {
                cout << d;
                return 0;
            }
            
            for(i = 1; i <= 6; i++)
            {
                if(cur + i > 100) break;
                
                nxt = arr[cur + i];
                if(!visited[nxt])
                {
                    que.push(nxt);
                    visited[nxt] = true;
                }
            }
        }
        
        d++;
    }
}
