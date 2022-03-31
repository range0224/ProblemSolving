#include<iostream>
using namespace std;

int n;
int arr[200010];

int main()
{
    int i;
    long long sum;
    long long ans;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    
    sum = 0;
    for(i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    
    sum /= n;
    
    ans = 0;
    for(i = 0; i < n; i++)
    {
        ans += abs(arr[i] - sum);
        
        arr[i + 1] += arr[i] - sum;
    }
    
    cout << ans;
}
