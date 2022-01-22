#include<iostream>
using namespace std;

int main()
{
    int a1, a0;
    int c;
    int n0;
    
    cin >> a1 >> a0;
    cin >> c;
    cin >> n0;
    
    if(a1 > c || a1 * n0 + a0 > c * n0) cout << 0;
    else cout << 1;
}
