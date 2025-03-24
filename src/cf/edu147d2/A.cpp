#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
constexpr int MOD = 1e9;

i64 qpow(i64 n, i64 q, i64 mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    string s;
    cin >> s;
    if (s[0] == '0') {
        cout << "0\n";
        return;
    }
    bool frist = false;
    if (s[0] == '?') {
        frist = true;
    }
    int cnt = count(s.begin(), s.end(), '?');
    if (frist) {
        cout << 9 * qpow(10, (cnt - 1)) << '\n';
    } else {
        cout << qpow(10, cnt) << '\n';
    }
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