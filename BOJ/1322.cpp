#include<iostream>
using namespace std;

int main()
{
    int n, m;
    long long ans;
    long long mul;
    
    cin >> n >> m;
    
    ans = 0;
    mul = 1;
    while(n)
    {
        if(n % 2 == 0)
        {
            ans += (m % 2) * mul;
            m /= 2;
        }
        n /= 2;
        mul <<= 1;
    }
    ans += m * mul;
    
    cout << ans;
}
