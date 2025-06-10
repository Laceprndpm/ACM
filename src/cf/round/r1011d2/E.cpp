#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;


void solve()
{
    i64 n;
    cin >> n;
    vector<i64> arr(n);
    vector<i64> brr(n);
    i64         suma = 0;
    i64         sumb = 0;
    for (i64& i : arr) {
        cin >> i;
        suma += i;
    }
    for (i64& i : brr) {
        cin >> i;
        sumb += i;
    }
    i64 minas = suma - sumb;
    sort(brr.begin(), brr.end());
    function<bool(int)> check = [&](int x) {
        auto        res = arr | ranges::views::transform([&](int y) {
                       return y % x;
                   });
        vector<int> res_vec(res.begin(), res.end());
        ranges::sort(res_vec);
        for (int i = 0; i < res_vec.size(); i++) {
            if (res_vec[i] != brr[i]) {
                return false;
            }
        }
        return true;
    };
    if (minas == 0) {
        if (check(1e8)) {
            cout << (i64)1e8 << '\n';
            return;
        } else {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= sqrtl(minas) + 1; i++) {
        if (minas % i == 0) {
            if (check(i)) {
                cout << i << '\n';
                return;
            }
            if (check(minas / i)) {
                cout << minas / i << '\n';
                return;
            }
        }
    }
    cout << -1 << '\n';
    return;
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