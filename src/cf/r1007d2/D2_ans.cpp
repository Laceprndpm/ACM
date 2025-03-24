#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int     n;
    int64_t l, r;
    cin >> n >> l >> r;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }
    if (n % 2 == 0) {
        n++;
        int cur = pref[n / 2] & 1;
        a.push_back(cur);
        pref.push_back(pref.back() + cur);
    }
    for (int i = n + 1; i <= n * 2; i++) {
        a.push_back(pref[i / 2] & 1);
        pref.push_back(pref[i - 1] + a[i]);
    }
    vector<int> even(n * 2 + 1);
    for (int i = 1; i <= n * 2; i++) {
        even[i] = even[i - 1] + (i & 1 ? 0 : a[i]);
    }
    int  p   = pref[n] & 1;
    auto get = [&](int64_t x) {
        int ret = 0;
        while (true) {
            if (x <= n * 2) {
                ret ^= a[x];
                break;
            }
            ret ^= p;
            if ((x / 2 - n) % 2 == 0) {
                break;
            }
            x /= 2;
        }
        return ret;
    };
    auto sum = [&](auto&& self, int64_t m) -> pair<int64_t, int64_t> {  // {sum even, sum odd}
        if (m <= n * 2) {
            return {even[m], pref[m] - even[m]};
        }
        int64_t eve = even[n * 2 - 1], odd = pref[n * 2 - 1] - eve;
        if (m % 2 == 0) {
            m += 1, odd -= get(m);
        }
        if (m / 2 % 2) {
            m += 1, eve -= get(m);
            m += 1, odd -= get(m);
        }
        auto [e, _] = self(self, m / 2);
        e -= even[n];
        int64_t c = m / 2 - n + 1, both = (p ? c - e : e);
        eve += both, odd += both;
        return {eve, odd};
    };
    int64_t ans   = 0;
    auto [re, ro] = sum(sum, r);
    ans += re + ro;
    auto [le, lo] = sum(sum, l - 1);
    ans -= le + lo;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
    }
}