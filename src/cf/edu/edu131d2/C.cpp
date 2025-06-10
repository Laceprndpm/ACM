#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> nwork(n + 1);
    vector<int> am(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> am[i];
        nwork[am[i]]++;
    }
    function<bool(i64)> check = [&](i64 x) {
        i64 remainworkercanDo = 0;
        i64 works             = 0;
        for (i64 i = 1; i <= n; i++) {
            if (nwork[i] <= x) {
                remainworkercanDo += (x - nwork[i]) / 2;
            } else {
                works += nwork[i] - x;
            }
        }
        return works <= remainworkercanDo;
    };
    i64 l = 0, r = 1e12;
    while (l < r) {
        i64 mid = (r - l) / 2 + l;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << '\n';
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