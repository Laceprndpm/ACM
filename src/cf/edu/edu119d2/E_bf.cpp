#include <iostream>
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
    int q;
    cin >> q;
    vector<int> ans;
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        int x, y;
        if (cmd == 1) {
            cin >> x;
            ans.push_back(x);
        } else {
            cin >> x >> y;
            for (int& i : ans) {
                if (i == x) i = y;
            }
        }
    }
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}