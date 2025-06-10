#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    set<pair<int, int>> point;
    int                 n;
    cin >> n;
    map<int, int> col;
    map<int, int> slide;
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        col[u]++;
        slide[u + v]++;
    }
    int ansC;
    for (auto [x, y] : col) {
        if (y % 2 != 0) {
            ansC = x;
            break;
        }
    }
    int su;
    for (auto [x, y] : slide) {
        if (y % 2 != 0) {
            su = x;
            break;
        }
    }
    cout << ansC << ' ' << su - ansC << '\n';
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