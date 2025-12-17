#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> bd(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> bd[i];
        bd[i] = '#' + bd[i] + '#';
    }
    bd[0] = bd[n + 1] = string(m + 2, '#');
    deque<i64>                    que;
    function<i64(i64 x, i64 y)>   zip   = [&](i64 x, i64 y) -> i64 { return x * (m + 2) + y; };
    function<pair<i64, i64>(i64)> unzip = [&](i64 x) -> pair<i64, i64> { return {x / (m + 2), x % (m + 2)}; };
    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            if (bd[i][j] == 'L') {
                que.push_back(zip(i, j));
            }
        }
    }
    int mx[] = {0, 0, -1, 1};
    int my[] = {1, -1, 0, 0};
    while (!que.empty()) {
        i64 top = que.front();
        que.pop_front();
        auto [x, y] = unzip(top);
        if (bd[x][y] == 'L') {
            for (int i = 0; i < 4; i++) {
                int nx = x + mx[i], ny = y + my[i];
                if (bd[nx][ny] == '.') {
                    que.push_back(zip(nx, ny));
                }
            }
        } else {
            int cnt = 0;
            for (int i = 0; i < 4; i++) {
                int nx = x + mx[i], ny = y + my[i];
                if (bd[nx][ny] == '.') {
                    cnt++;
                }
            }
            if (cnt <= 1) {
                bd[x][y] = '+';
                for (int i = 0; i < 4; i++) {
                    int nx = x + mx[i], ny = y + my[i];
                    if (bd[nx][ny] == '.') {
                        que.push_back(zip(nx, ny));
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << bd[i][j];
        }
        cout << '\n';
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}