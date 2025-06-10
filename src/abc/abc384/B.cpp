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
    function<bool(int, int)> check = [&](int dv, int y) -> bool {
        if (dv == 1) {
            return 1600 <= y && y <= 2799;
        } else {
            return 1200 <= y && y <= 2399;
        }
    };
    int n, r;
    cin >> n >> r;
    while (n--) {
        int d, ra;
        cin >> d >> ra;
        if (check(d, r)) {
            r += ra;
        }
    }
    cout << r << '\n';
    return 0;
}