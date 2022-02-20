#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;
vector<int> mn, mx;

int main()
{
    int i;
    int a, b;
    
    cin >> n;
    for(i = 0; i < n; i++)
    {
        cin >> a >> b;
        
        v.push_back(make_pair(a, b));
        mn.push_back(a - b);
        mx.push_back(a + b);
    }
    
    sort(mn.begin(), mn.end());
    sort(mx.begin(), mx.end());
    
    for(i = 0; i < n; i++)
    {
        cout << lower_bound(mx.begin(), mx.end(), v[i].first - v[i].second) - mx.begin() + 1 << ' ';
        cout << upper_bound(mn.begin(), mn.end(), v[i].first + v[i].second) - mn.begin() << '\n';
    }
}
