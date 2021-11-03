#include<iostream>
using namespace std;

int main()
{
    int n;
    long long a, b;
    int x, y;
    
    cin >> n;
    
    x = n + 1;
    y = n + 2;
    a = n;
    b = n + 2;
    while(a != b)
    {
        if(a < b)
        {
            b -= x + 1;
            a += x;
            x++;
        }
        else
        {
            y++;
            b += y;
        }
    }
    
    cout << n << ' ' << x << ' ' << y;
}
