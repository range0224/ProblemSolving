#include<iostream>
#include<queue>
using namespace std;

int n, m, k, q;
int arr[200010];
int limit[200010];
int grow[200010];
int query[200010][3];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq[200010];
int ans[200010];
bool visited[200010];

int main()
{
    int i;
    int a, b, c;
    int x;
    int idx;
    int cnt;

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> n >> m >> k >> q;
    for (i = 1; i <= m; i++)
    {
        cin >> limit[i];
    }
    for (i = 0; i < k; i++)
    {
        cin >> grow[i];
    }
    for (i = 0; i < q; i++)
    {
        cin >> a >> b >> c;

        query[i][0] = a;
        query[i][1] = b;
        query[i][2] = c;

        pq[a].push(make_pair(limit[c] / 2, i));
        pq[b].push(make_pair(limit[c] / 2, i));
    }

    cnt = 0;
    for (i = 0; i < k; i++)
    {
        x = grow[i];

        if (i >= 2 && ans[i - 1] > ans[i - 2]) arr[x] += 2;
        else arr[x]++;

        while (!pq[x].empty() && pq[x].top().first <= arr[x])
        {
            idx = pq[x].top().second;
            pq[x].pop();

            if (visited[idx]) continue;

            a = query[idx][0];
            b = query[idx][1];
            c = query[idx][2];

            if (arr[a] + arr[b] >= limit[c])
            {
                visited[idx] = true;
                cnt++;
            }
            else
            {
                pq[a].push(make_pair(arr[a] + (limit[c] - arr[a] - arr[b] + 1) / 2, idx));
                pq[b].push(make_pair(arr[b] + (limit[c] - arr[a] - arr[b] + 1) / 2, idx));
            }
        }

        ans[i] = cnt;
    }

    for (i = 0; i < k; i++)
    {
        cout << ans[i] << '\n';
    }
}
