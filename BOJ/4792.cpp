#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;
int par[1010];
vector<pair<int, int>> red, blue;

int find(int x)
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);
}

void union_(int a, int b)
{
    a = find(a);
    b = find(b);
    
    par[a] = b;
}

int main()
{
    int i;
    char a;
    int b, c;
    int cnt;
    int linked;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    
    while(1)
    {
        cin >> n >> m >> k;
        
        if(!n && !m && !k) break;
        
        for(i = 1; i <= n; i++) par[i] = i;
        
        red.clear();
        blue.clear();
        for(i = 0; i < m; i++)
        {
            cin.ignore();
            
            cin >> a >> b >> c;
            
            if(a == 'R') red.push_back(make_pair(b, c));
            else blue.push_back(make_pair(b, c));
        }
        
        cnt = 0;
        linked = 0;
        for(i = 0; i < blue.size(); i++)
        {
            if(find(blue[i].first) != find(blue[i].second))
            {
                union_(blue[i].first, blue[i].second);
                cnt++;
                linked++;
            }
        }
        
        for(i = 0; i < red.size(); i++)
        {
            if(find(red[i].first) != find(red[i].second))
            {
                union_(red[i].first, red[i].second);
                linked++;
            }
            else if(cnt > k) cnt--;
        }
        
        if(linked == n - 1 && cnt == k) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}
