#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int         n;
    vector<int> l, r;
    int         a, b;
    cin >> n >> a >> b;
    vector<int> vis(n + 1);
    for (int i = b + 1; i <= n; i++) {
        l.push_back(i);
    }
    for (int i = 1; i < a; i++) {
        r.push_back(i);
    }
    if (a < b) l.push_back(a), r.push_back(b);
    for (int i = a + 1; i <= b - 1; i++) {
        if (l.size() < n / 2) {
            l.push_back(i);
        } else {
            r.push_back(i);
        }
    }
    if (l.size() != r.size() || l.size() + r.size() != n) {
        cout << -1;
    } else {
        for (int i : l) {
            cout << i << ' ';
        }
        for (int i : r) {
            cout << i << ' ';
        }
    }
    cout << '\n';
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