#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
int arr[1010];

int main()
{
    int i;
    
    cin >> n >> m;

    for(i = 1; i <= m; i++)
    {
        arr[i] = i;
        n -= i;
    }
    
    if(n < 0)
    {
        cout << -1;
        return 0;
    }
    
    cout << arr[m] - arr[1] + (n % m != 0);
}
