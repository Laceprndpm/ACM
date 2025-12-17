#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    int              offset = m - 1;
    vector<set<int>> arr(n + m);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        int  place = x - y + offset;
        auto it    = arr[place].find(x);
        i64  l1_cnt;

        if (it == arr[place].end()) {
            // 在第一个格子
            auto [it, _] = arr[place].insert(x);
            if (it == arr[place].begin()) {
                l1_cnt = (x - 1) * 2;
            } else {
                l1_cnt = (x - *prev(it)) * 2 - 1;
            }
            
        }
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