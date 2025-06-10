#include <queue>
#include <tuple>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void BFS()
{
    int m;
    using three = tuple<int, int, int>;
    queue<three> q;
    q.emplace(1, 2, 3);
    while (!q.empty()) {
        auto [x, y, z] = q.front();
        q.pop();
        cout << '?' << ' ' << x << ' ' << y << ' ' << z << endl;
        cin >> m;
        if (m == 0) {
            cout << '!' << ' ' << x << ' ' << y << ' ' << z << endl;
            return;
        } else {
            q.emplace(x, y, m);
            q.emplace(x, m, z);
            q.emplace(m, y, z);
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    BFS();
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