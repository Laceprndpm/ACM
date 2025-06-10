#include <cassert>
#include <deque>
#include <iostream>
#include <set>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    set<pair<int, int>> st;
    int                 s, k;
    cin >> s >> k;
    deque<pair<int, int>> q;
    q.push_back({0, k});
    int last = k;
    if (s % k == 0) {
        cout << k << '\n';
        return;
    }
    if (s >= k * k) {
        cout << max(k - 2, 1) << '\n';
        return;
    }
    while (true) {
        auto [l, x] = q.front();
        q.pop_front();
        if (l == s || x == 1) {
            cout << x << '\n';
            return;
        }
        if (x != last) {
            last = x;
            st   = set<pair<int, int>>();
        }
        if ((k - x) % 2 == 0) {
            if (l + x <= s) {
                if (!st.contains({l, x})) {
                    q.push_front({l + x, x});
                    q.push_back({l + x, x - 1});
                    st.insert({l, x});
                }
            }
        } else {
            if (l - x >= 0) {
                if (!st.contains({l, x})) {
                    q.push_front({l - x, x});
                    q.push_back({l - x, x - 1});
                    st.insert({l, x});
                }
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