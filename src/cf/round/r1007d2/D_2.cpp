#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    i64 l, r;
    cin >> n >> l >> r;
    vector<int> arr(2 * n + 100);
    int         i = 1;
    for (; i <= n; i++) {
        cin >> arr[i];
    }
    vector<int> prefixXOR(2 * n + 100);
    for (int i = 1; i <= n; i++) {
        prefixXOR[i] = prefixXOR[i - 1] ^ arr[i];
    }
    n = max(n, 5);
    if (n % 2 == 0) {
        ++n;
    }
    for (; i <= 2 * n; i++) {
        arr[i]       = prefixXOR[i / 2];
        prefixXOR[i] = arr[i] ^ prefixXOR[i - 1];
    }
    // n = max(10, n);
    // for (; i <= 2 * n; i++) {
    //     arr[i]       = prefixXOR[i / 2];
    //     prefixXOR[i] = arr[i] ^ prefixXOR[i - 1];
    // }
    vector<i64> prefixEven(2 * n + 1), prefixOdd(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        prefixEven[i] = prefixEven[i - 1], prefixOdd[i] = prefixOdd[i - 1];
        if (i % 2 == 1) {
            prefixOdd[i] += arr[i];
        } else {
            prefixEven[i] += arr[i];
        }
    }
    function<i64(i64 u)> single = [&](i64 u) -> i64 {
        if (u <= 2 * n) {
            return arr[u];
        }
        if ((u / 2) % 2) {
            return prefixXOR[n];
        } else {
            return single(u / 2) ^ prefixXOR[n];
        }
    };
    i64                p = prefixXOR[n];
    function<i64(i64)> both;
    function<i64(i64)> sumOdd = [&](i64 u) -> i64 {
        if (u == 0) {
            return 0;
        }
        if (u % 2 == 0) {
            u--;
        }
        if (u >= 2 * n) {
            i64 ans = 0;
            if (u % 4 == 3) {
                u += 2;
                ans -= single(u);
            }
            return ans + prefixOdd[2 * n - 1] + both(u);
        } else
            return prefixOdd[u];
    };
    function<i64(i64 u)> sumEven = [&](i64 u) -> i64 {  // 计算[0, u, 2]所有偶数
        if (u % 2 == 1) {
            u--;
        }
        if (u > 2 * n) {
            i64 ans = 0;
            if (u % 4 == 2) {
                u += 3;
                ans -= single(u - 1);
            } else {
                u += 1;
            }
            return ans + prefixEven[2 * n - 1] + both(u);
        } else
            return prefixEven[u];
    };
    function<i64(i64)> e = [&](i64 u) -> i64 {
        assert(u % 4 == 1);
        return sumEven(u / 2ll) - prefixEven[n];
    };
    both = [&](i64 m) -> i64 {  // 计算[2 * n, m - 1, 2]
        // while (u % 4 != 1) {
        //     u++;
        //     ans -= single(u);
        // }
        assert(m % 4 == 1);
        assert(m >= 2 * n);
        if (p == 0) {
            return e(m);
        } else {
            return (m / 2 - n + 1) - e(m);
        }
    };

    function<i64(i64 u)> ma = [&](i64 u) -> i64 {
        return (sumEven(u) + sumOdd(u));
    };
    // cout << ma(l - 1) << '\n';
    // cout << single(r) << '\n';
    cout << ma(r) - ma(l - 1) << '\n';
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
    while (t--)
        solve();
    return 0;
}