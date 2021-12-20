#include<iostream>
#include<algorithm>
using namespace std;

int n;
int arr[100010][2];
int prefix[1000020];
int ans;

int main()
{
    int i;
    int sum;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> arr[i][0] >> arr[i][1];
    }
    
    for(i = 0; i < n; i++)
    {
        arr[i][0] += 500010;
        arr[i][1] += 500010;
    }
    arr[n][0] = arr[0][0];
    arr[n][1] = arr[0][1];
    
    for(i = 1; i <= n; i++)
    {
        if(arr[i][0] != arr[i - 1][0])
        {
            prefix[min(arr[i][0], arr[i - 1][0])]++;
            prefix[max(arr[i][0], arr[i - 1][0])]--;
        }
    }
    
    sum = 0;
    for(i = 0; i < 1000020; i++)
    {
        sum += prefix[i];
        
        ans = max(ans, sum);
    }
    
    for(i = 0; i < 1000020; i++) prefix[i] = 0;
    
    for(i = 1; i <= n; i++)
    {
        if(arr[i][1] != arr[i - 1][1])
        {
            prefix[min(arr[i][1], arr[i - 1][1])]++;
            prefix[max(arr[i][1], arr[i - 1][1])]--;
        }
    }
    
    sum = 0;
    for(i = 0; i < 1000020; i++)
    {
        sum += prefix[i];
        
        ans = max(ans, sum);
    }
    
    cout << ans;
}
