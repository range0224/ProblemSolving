#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, m;
priority_queue<int, vector<int>, greater<int>> pq;

int main()
{
    int t;
    string a;
    int b;
    int ans;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        
        ans = 0;
        while(n--)
        {
            cin >> a;
            
            if(a[0] == 'i')
            {
                cin >> b;
                
                ans ^= b;
                pq.push(b);
                if(pq.size() > m)
                {
                    ans ^= pq.top();
                    pq.pop();
                }
            }
            else
            {
                cout << ans << '\n';
            }
        }
        
        while(!pq.empty()) pq.pop();
    }
}
