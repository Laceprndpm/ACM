#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 MOD = 998244353;
vector<i64>   frc((i64)2e5 + 1);
vector<i64>   frc1((i64)2e5 + 1);

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
    string str01;
    cin >> str01;
    char lst   = 2;
    int  cur   = 1;
    i64  ans   = 1;
    i64  times = 0;
    i64  upper = 0;
    i64  div   = 1;
    for (char c : str01) {
        if (c == lst) {
            cur++;
        } else {
            lst = c;
            ans *= frc[cur];
            ans %= MOD;
            times += (cur - 1) % MOD;
            upper += (cur - 1);
            div *= frc1[cur - 1];
            div %= MOD;
            cur = 1;
        }
    }
    ans *= frc[cur];
    times += cur - 1;
    ans %= MOD;
    times %= MOD;
    upper += (cur - 1);
    div *= frc1[cur - 1];
    div %= MOD;

    ans *= frc[upper];
    ans %= MOD;
    ans *= div;
    ans %= MOD;
    cur = 1;
    ans += MOD;
    ans %= MOD;
    cout << times << ' ';
    cout << ans << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    frc[0] = 1;
    for (int i = 1; i <= (i64)2e5; i++) {
        frc[i] = frc[i - 1] * i % MOD;
    }
    frc1[(i64)2e5] = qpow(frc[(i64)2e5], MOD - 2);
    for (int i = (i64)2e5 - 1; i >= 0; i--) {
        frc1[i] = frc1[i + 1] * (i + 1) % MOD;
    }
    while (t--) {
        solve();
    }
    return 0;
}

// 1 4
// 1 3
// 2 3
// 2 4
// 4 1
// 4 2
// 5 1
// 5 2