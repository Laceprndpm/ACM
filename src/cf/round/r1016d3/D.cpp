#include <iostream>
#include <ostream>
#include <utility>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
#define int long long
constexpr int INF = 1e9;
int           n;

int aaaaaaaaac = 1;
ostream& operator<<(ostream& os, const pair<i64, i64>& x)
{
    os << x.first << ' ' << x.second;
    return os;
}

i64 dfs1(i64 l, i64 r, i64 x, i64 y, i64 cur, i64 remains)
{
    if (remains == 0LL) return cur;
    i64 lm = l + (1ll << (remains - 1ll));
    i64 rm = r + (1ll << (remains - 1ll));
    if (x < lm) {
        if (y < rm) {
            return dfs1(l, r, x, y, cur, remains - 1ll);
        } else {
            return dfs1(l, rm, x, y, cur + 3LL * (1ll << (2LL * (remains - 1ll))), remains - 1ll);
        }
    } else {
        if (y < rm) {
            return dfs1(lm, r, x, y, cur + 2LL * (1ll << (2LL * (remains - 1ll))), remains - 1ll);
        } else {
            return dfs1(lm, rm, x, y, cur + 1ll * (1ll << (2LL * (remains - 1ll))), remains - 1ll);
        }
    }
}

i64 dfs1ll(i64 x, i64 y)
{
    return dfs1(1ll, 1ll, x, y, 1ll, n);
}

pair<i64, i64> dfs2(i64 l, i64 r, i64 cur, i64 remains)
{
    if (remains == 0LL) {
        return {l, r};
    }
    if (cur > 3LL * (1ll << 2LL * (remains - 1ll))) {
        return dfs2(l, r + (1ll << (remains - 1ll)), cur - 3LL * (1ll << 2LL * (remains - 1ll)), remains - 1ll);
    } else if (cur > 2LL * (1ll << 2LL * (remains - 1ll))) {
        return dfs2(l + (1ll << (remains - 1ll)), r, cur - 2LL * (1ll << 2LL * (remains - 1ll)), remains - 1ll);
    } else if (cur > 1ll * (1ll << 2LL * (remains - 1ll))) {
        return dfs2(l + (1ll << (remains - 1ll)), r + (1ll << (remains - 1ll)),
                    cur - 1ll * (1ll << 2LL * (remains - 1ll)), remains - 1ll);
    } else {
        return dfs2(l, r, cur, remains - 1ll);
    }
}

pair<i64, i64> dfs2(i64 cur)
{
    return dfs2(1ll, 1ll, cur, n);
}

void solve()
{
    cin >> n;
    int q;
    cin >> q;
    while (q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "->") {
            i64 x, y;
            cin >> x >> y;
            cout << dfs1ll(x, y) << '\n';
        } else {
            i64 x;
            cin >> x;
            cout << dfs2(x) << '\n';
        }
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0LL);
    cout.tie(0LL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0LL;
}