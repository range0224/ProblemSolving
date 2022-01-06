#include<iostream>
#include<vector>
#include<set>
using namespace std;

int n;
int arr[10];
vector<int> v;
set<pair<pair<int, int>, int>> s;

void recur(int cur)
{
    int i;
    int a, b, c;
    
    if(cur == n){
        a = 0;
        b = 0;
        c = 0;
        
        if(v[0] != 0) a = v[0];
        if(v[1] != 0) b = v[1];
        if(v[2] != 0) c = v[2];
        
        if(v[3] != 0){
            if(a != 0 && b == 0) b = v[3] - a;
            if(a == 0 && b != 0) a = v[3] - b;
            if(v[6] != 0 && c == 0) c = v[6] - v[3];
        }
        if(v[4] != 0){
            if(b != 0 && c == 0) c = v[4] - b;
            if(b == 0 && c != 0) b = v[4] - c;
            if(v[6] != 0 && a == 0) a = v[6] - v[4];
        }
        if(v[5] != 0){
            if(c != 0 && a == 0) a = v[5] - c;
            if(c == 0 && a != 0) c = v[5] - a;
            if(v[6] != 0 && b == 0) b = v[6] - v[5];
        }
        
        if(a < 1 || a > b || b > c) return;
        if(v[0] != 0 && a != v[0]) return;
        if(v[1] != 0 && b != v[1]) return;
        if(v[2] != 0 && c != v[2]) return;
        if(v[3] != 0 && a + b != v[3]) return;
        if(v[4] != 0 && b + c != v[4]) return;
        if(v[5] != 0 && c + a != v[5]) return;
        if(v[6] != 0 && a + b + c != v[6]) return;
        
        s.insert(make_pair(make_pair(a, b), c));
        
        return;
    }
    
    for(i = 0; i < 7; i++){
        if(v[i]) continue;
        
        v[i] = arr[cur];
        recur(cur + 1);
        v[i] = 0;
    }
}

int main()
{
    int t;
    int i;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    v.resize(10, 0);
    
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        
        s.clear();
        recur(0);
        
        cout << s.size() << '\n';
    }
}
