#include<iostream>
using namespace std;

long long n, m;

long long check(long long x)
{
    int cnt[10] = {0};
    int t = 0;
    int i;
    long long sum;
    
    while(x)
    {
        t++;
        
        if(cnt[x % m])
        {
            sum = 1;
            for(i = 0; i < cnt[x % m] - 1; i++)
            {
                sum *= m;
            }
            
            return sum;
        }
        cnt[x % m] = t;
        x /= m;
    }
    
    if(t < m) return -1;
    
    return 0;
}

bool check2(long long x)
{
    int cnt = 0;
    
    while(x)
    {
        cnt++;
        x /= m;
    }
    
    return cnt <= m;
}

int main()
{
    long long x;
    int i;
    
    cin >> n >> m;
    
    n++;
    
    while(1)
    {
        if(!check2(n))
        {
            cout << -1;
            return 0;
        }
        
        x = check(n);
        
        if(x == -1)
        {
            n = 1;
            for(i = 0; i < m - 1; i++)
            {
                n *= m;
            }
        }
        else if(x == 0)
        {
            cout << n;
            return 0;
        }
        else
        {
            n = (n / x + 1) * x;
        }
    }
}
