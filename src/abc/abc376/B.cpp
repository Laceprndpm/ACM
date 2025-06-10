#include <functional>
#include <iostream>
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
    int l = 1, r = 2;
    int n, q;
    cin >> n >> q;
    function<int(int st, int ed, int mid)> work = [&](int st, int ed, int mid) -> int {
        st = (n + st - mid) % n;
        ed = (n + ed - mid) % n;
        return abs(st - ed);
    };
    int ans = 0;
    while (q--) {
        char cmd;
        cin >> cmd;
        int target;
        cin >> target;
        if (cmd == 'L') {
            ans += work(l, target, r);
            l = target;
        } else {
            ans += work(r, target, l);
            r = target;
        }
    }
    cout << ans << '\n';
    return 0;
}