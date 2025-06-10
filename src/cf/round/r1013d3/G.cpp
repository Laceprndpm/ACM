#include <deque>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    // set<pair<int, int>> st;
    // int                 s, k;
    // cin >> s >> k;
    // deque<pair<int, int>> q;
    // q.push_back({0, k});
    // int last = k;
    // while (true) {
    //     auto [l, x] = q.front();
    //     q.pop_front();
    //     if (l == s || x == 1) {
    //         cout << x << '\n';
    //         return;
    //     }
    //     if (x != last || st.size() >= 2e6) {
    //         last = x;
    //         st = set<pair<int, int>>();
    //     }
    //     if ((k - x) % 2 == 0) {
    //         if (l + x <= s) {
    //             if (!st.contains({l + x, x})) {
    //                 q.push_front({l + x, x});
    //                 q.push_back({l + x, x - 1});
    //                 st.insert({l, x});
    //             }
    //         }
    //     } else {
    //         if (l - x >= 0) {
    //             if (!st.contains({l, x})) {
    //                 q.push_front({l - x, x});
    //                 q.push_back({l - x, x - 1});
    //                 st.insert({l, x});
    //             }
    //         }
    //     }
    // }
    int s, k;
    cin >> s >> k;
    vector<bool> vis(s + 1);
    for (int i = k; i >= 2; i--) {
        if ((k - i) % 2 == 0) {  // 往前划
            for (int x = s; x >= 0; x--) {
                vis[x] = x >= i && vis[x - i];
            }
            for (int x = i; x <= s; x++) {
                vis[x] = vis[x] || vis[x - i];
            }
        } else {
            for (int x = 0; x <= s; x++) {
                vis[x] = x + i <= s && vis[x + i];
            }
            for (int x = s - i; x >= 0; x--) {
                vis[x] = vis[x] || vis[x + i];
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