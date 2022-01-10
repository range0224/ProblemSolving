#include<iostream>
#include<set>
#include<algorithm>
using namespace std;

int n;
int arr[1010];
set<int> s;

int main()
{
    int t;
    int i, j;
    int cnt;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    cin >> t;
    while(t--)
    {
        s.clear();
        
        cin >> n;
        for(i = 0; i < n; i++)
        {
            cin >> arr[i];
            s.insert(arr[i]);
        }
        
        sort(arr, arr + n);
        
        cnt = 0;
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(s.find(arr[j] + arr[j] - arr[i]) != s.end()) cnt++;
            }
        }
        
        cout << cnt << '\n';
    }
}
