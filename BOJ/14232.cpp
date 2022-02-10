#include<iostream>
#include<vector>
using namespace std;

int main()
{
    long long n;
    vector<long long> v;
    long long i;
    long long x;
    
    cin >> n;
    
    x = n;
    for(i = 2; i * i <= n; i++)
    {
        while(x % i == 0)
        {
            v.push_back(i);
            x /= i;
        }
    }
    
    if(x != 1) v.push_back(x);
    
    cout << v.size() << '\n';
    for(i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }
}
