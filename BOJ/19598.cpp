#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;
multiset<int> room;

bool comp(pair<int, int> a, pair<int, int> b) {
    return a.second < b.second;
}

int main() {
    int i, j;
    int a, b;
    
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> a >> b;

        v.push_back(make_pair(a, b));
    }

    sort(v.begin(), v.end(), comp);

    room.insert(v[0].second);
    for (i = 1; i < n; i++) {
        auto it = room.upper_bound(v[i].first);

        if (it == room.begin()) room.insert(v[i].second);
        else {
            it--;
            room.insert(v[i].second);
            room.erase(it);
        }
    }

    cout << room.size();
}
