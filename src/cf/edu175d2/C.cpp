#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> penalty(n);
    for (int& i : penalty) {
        cin >> i;
    }
    function<bool(int x)> check = [&](int x) {
        char last = 'R';
        int  cnt  = 0;
        for (int i = 0; i < n; i++) {
            if (penalty[i] > x) {
                if (last != s[i]) {
                    last = s[i];
                    if (last == 'B') {
                        cnt++;
                        if (cnt > k) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    };
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = (r - l) / 2 + l;
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