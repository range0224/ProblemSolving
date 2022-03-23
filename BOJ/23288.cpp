#include<iostream>
using namespace std;

int n, m;
int arr[30][30];
bool visited[30][30];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int dice[6] = { 1, 6, 4, 3, 5, 2 };
int ddice[4][6] = { {5, 4, 2, 3, 0, 1}, {2, 3, 1, 0, 4, 5}, {4, 5, 2, 3, 1, 0}, {3, 2, 0, 1, 4, 5} };
int x, y, dir;

bool in_range(int x, int y) {
    return x >= 0 && x < n&& y >= 0 && y < m;
}

void rotate() {
    int temp[6];

    for (int i = 0; i < 6; i++) {
        temp[i] = dice[ddice[dir][i]];
    }

    for (int i = 0; i < 6; i++) {
        dice[i] = temp[i];
    }
}

int dfs(int x, int y) {
    int ret = 1;
    int nx, ny;

    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        nx = x + dx[i];
        ny = y + dy[i];

        if (!in_range(nx, ny) || visited[nx][ny] || arr[nx][ny] != arr[x][y]) continue;

        ret += dfs(nx, ny);
    }

    return ret;
}

int main()
{
    int q;
    int nx, ny;
    int ans = 0;

    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }

    dir = 1;
    while (q--) {
        nx = x + dx[dir];
        ny = y + dy[dir];

        if (!in_range(nx, ny)) dir = (dir + 2) % 4;

        x += dx[dir];
        y += dy[dir];

        rotate();

        if (arr[x][y] > dice[1]) dir = (dir + 1) % 4;
        else if (arr[x][y] < dice[1]) dir = (dir + 3) % 4;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                visited[i][j] = false;
            }
        }

        ans += arr[x][y] * dfs(x, y);
    }

    cout << ans;
}
