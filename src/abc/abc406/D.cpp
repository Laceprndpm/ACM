#include <iostream>
#include <map>
#include <set>
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
    int h, w, n;
    cin >> h >> w >> n;
    map<int, set<int>> xSt;
    map<int, set<int>> ySt;
    for (int i = 0; i < n; i++) {
        int xi, yi;
        cin >> xi >> yi;
        xSt[xi].insert(yi);
        ySt[yi].insert(xi);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int cmd, x;
        cin >> cmd >> x;
        if (cmd == 1) {
            cout << xSt[x].size() << '\n';
            for (int y : xSt[x]) {
                ySt[y].extract(x);
            }
            xSt.erase(x);
        } else {
            cout << ySt[x].size() << '\n';
            for (int y : ySt[x]) {
                xSt[y].extract(x);
            }
            ySt.erase(x);
        }
    }
    return 0;
}