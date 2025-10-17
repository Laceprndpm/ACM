#include <cassert>
#include <iostream>
using namespace std;
using i64 = long long;

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    assert(n);
    assert(n % 2 == 0);
    string s;
    cin >> s;
    auto check = [&](int x) {
        string scopy = s;
        int    cnt   = x;
        for (int i = 0; i < n; i++) {
            if (cnt == 0) break;
            if (scopy[i] == ')') {
                scopy[i] = '(';
                cnt--;
            }
        }
        cnt = x;
        for (int i = n - 1; i >= 0; i--) {
            if (cnt == 0) break;
            if (scopy[i] == '(') {
                scopy[i] = ')';
                cnt--;
            }
        }
        int val = 0;
        for (int i = 0; i < n; i++) {
            if (scopy[i] == '(') {
                val++;
            } else {
                val--;
            }
            if (val < 0) return false;
        }
        return true;
    };
    i64 l = 0, r = n / 2;
    i64 ans = -1;
    while (l <= r) {
        i64 mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
