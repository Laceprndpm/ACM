#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m, q;
    cin >> n >> m >> q;
    vector<bool>     all(n + 1);
    vector<set<int>> user(n + 1);
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int x, y;
            cin >> x >> y;
            user[x].insert(y);
        } else if (cmd == 2) {
            int x;
            cin >> x;
            all[x] = true;
        } else {
            int x, y;
            cin >> x >> y;
            if (all[x] || user[x].count(y)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}