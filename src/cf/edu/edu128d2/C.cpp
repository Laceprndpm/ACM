#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    i64         slen = s.length();
    i64         cnt1 = 0;
    i64         cnt0 = count(s.begin(), s.end(), '0');
    vector<i64> prefix(slen);
    vector<i64> suffix(slen);
    for (int i = 0; i < slen; i++) {
        if (s[i] == '1') {
            cnt1++;
        } else {
            prefix[cnt1]++;
        }
    }
    for (int i = 1; i <= cnt1; i++) {
        prefix[i] += prefix[i - 1];
    }
    cnt1 = 0;
    for (int i = slen - 1; i >= 0; i--) {
        if (s[i] == '1') {
            cnt1++;
        } else {
            suffix[cnt1]++;
        }
    }
    for (int i = 1; i <= cnt1; i++) {
        suffix[i] += suffix[i - 1];
    }
    function<bool(int)> check = [&](int x) {
        for (int i = 0; i <= x; i++) {
            if (cnt0 - (prefix[i] + suffix[x - i]) <= x) {
                return true;
            }
        }
        return false;
    };
    int l = 0, r = cnt0;
    while (l < r) {
        int mid = (r + l) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << '\n';
    // vector<i64> cnt1(slen + 1);
    // cnt1[0] = (s[0] == '1');
    // for (int i = 1; i < slen; i++) {
    //     cnt1[i] = cnt1[i - 1] + (s[i] == '1');
    // }
    // cnt1[slen]       = cnt1[slen - 1];
    // i64 remainLength = cnt1[slen - 1];
    // if (remainLength == slen || remainLength == 0) {
    //     cout << 0 << '\n';
    //     return;
    // }
    // i64 ans = INT64_MAX;
    // for (i64 l = 0; l + remainLength - 1 <= slen; l++) {
    //     ans = min(remainLength - cnt1[l + remainLength - 1] + (l != 0 ? cnt1[l - 1] : 0), ans);
    // }
    // cout << ans << '\n';
    // i64         cnt0 = count(s.begin(), s.end(), '0');
    // i64         len  = s.length();
    // vector<i64> costPre(len);
    // vector<i64> costSuf(len);
    // for (int i = 0; i < len; i++) {
    //     if (i == 0)
    //         costPre[i] = ((s[i] == '0') ? 1 : -1);
    //     else
    //         costPre[i] = costPre[i - 1] + ((s[i] == '0') ? 1 : -1);
    // }
    // for (int i = len - 1; i >= 0; i--) {
    //     if (i == len - 1)
    //         costSuf[i] = ((s[i] == '0') ? 1 : -1);
    //     else
    //         costSuf[i] = costSuf[i + 1] + ((s[i] == '0') ? 1 : -1);
    // }
    // costPre[0] = max(costPre[0], 0ll);

    // for (int i = 1; i < len; i++) {
    //     costPre[i] = max(max(costPre[i], costPre[i - 1]), 0ll);
    // }
    // costSuf[len - 1] = max(costSuf[len - 1], 0ll);
    // for (int i = len - 2; i >= 0; i--) {
    //     costSuf[i] = max(max(costSuf[i], costSuf[i + 1]), 0ll);
    // }
    // i64 minas = INT64_MIN;
    // for (int i = 0; i < len - 2; i++) {
    //     minas = max(minas, costPre[i] + costSuf[i + 1]);
    // }
    // cout << cnt0 - minas << '\n';
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
    // cnt1[n]  -  (cnt1[r] - cnt1[l-1])
    // r - l + 1 - (cnt1[r] - cnt1[l-1])
    //
    // r - l + 1 <= cnt1[n],r-l+1==cnt1[n]
    // r - l + 1 > cnt1[n]
    // r - l + 1 - cnt1[r] + cnt1[l-1]，不合适
    //
    //
}