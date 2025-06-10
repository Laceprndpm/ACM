#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
vector<i64>   prefixA, prefixB;
int           n, m;

i64 sea(int k)
{
    int L = 0, R = k;
    L = max(L, 2 * k - m), R = min(k, n - k);
    function<i64(int x)> f = [&](int x) -> i64 {
        // if (x * 2 + (k - x) > n || x > m || (k - x) * 2 + x > m || (k - x) > n) return 0;
        // if (x * 2 + (k - x) > n || x > m || (k - x) * 2 + x > m || (k - x) > n) return 0;
        //  x * 2 + (k - x) <= n, x <= m, x >= 2 * k - m, x >= k - n
        return prefixA[x] + prefixB[k - x];
    };
    while (R - L > 3) {
        int delta = (R - L) / 3;
        int m1 = L + delta, m2 = R - delta;
        if (f(m1) > f(m2)) {
            R = m2;
        } else {
            L = m1;
        }
    }
    i64 mx = 0;
    for (int i = L; i <= R; i++) {
        mx = max(f(i), mx);
    }
    return mx;
}

void solve()
{
    cin >> n >> m;
    vector<i64> arrA(n), arrB(m);
    for (int i = 0; i < n; i++) {
        cin >> arrA[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> arrB[i];
    }
    sort(arrA.begin(), arrA.end()), sort(arrB.begin(), arrB.end());
    prefixA.clear(), prefixB.clear();
    prefixA.push_back(0), prefixB.push_back(0);
    i64 last = 0;
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        last += arrA[j] - arrA[i];
        prefixA.push_back(last);
    }
    last = 0;
    for (int i = 0, j = m - 1; i < j; i++, j--) {
        last += arrB[j] - arrB[i];
        prefixB.push_back(last);
    }
    int bound = min({(n + m) / 3, n, m});
    cout << bound << '\n';
    for (int k = 1; k <= bound; k++) {
        cout << sea(k) << ' ';
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