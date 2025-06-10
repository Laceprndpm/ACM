#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    map<i64, vector<i64>> x;
    map<i64, vector<i64>> y;
    i64                   n, m, curX, curY;
    cin >> n >> m >> curX >> curY;
    for (i64 i = 0; i < n; i++) {
        i64 u, v;
        cin >> u >> v;
        x[u].push_back(v);
        y[v].push_back(u);
    }
    for (auto &[_, i] : x) {
        sort(i.begin(), i.end());
    }
    for (auto &[_, i] : y) {
        sort(i.begin(), i.end());
    }
    set<pair<i64, i64>> st;
    for (i64 i = 0; i < m; i++) {
        char cmd;
        i64  len;
        i64  l, r;
        cin >> cmd >> len;
        if (cmd == 'U' || cmd == 'D') {
            if (cmd == 'D') {
                l = curY - len;
                r = curY;
                curY -= len;
            } else {
                l = curY;
                r = curY + len;
                curY += len;
            }
            if (x.count(curX) == 0) continue;
            auto liter = lower_bound(x[curX].begin(), x[curX].end(), l);
            auto riter = upper_bound(x[curX].begin(), x[curX].end(), r);
            if (liter < riter) {
                for (auto i = liter; i != riter; i++) {
                    st.insert({curX, *i});
                }
                x[curX].erase(liter, riter);
            }
        } else {
            if (cmd == 'L') {
                l = curX - len;
                r = curX;
                curX -= len;
            } else {
                l = curX;
                r = curX + len;
                curX += len;
            }
            if (y.count(curY) == 0) continue;
            auto liter = lower_bound(y[curY].begin(), y[curY].end(), l);
            auto riter = upper_bound(y[curY].begin(), y[curY].end(), r);
            if (liter < riter) {
                for (auto i = liter; i != riter; i++) {
                    st.insert({*i, curY});
                }
                y[curY].erase(liter, riter);
            }
        }
    }
    cout << curX << ' ' << curY << ' ' << st.size();
    return 0;
}