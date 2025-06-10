#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    int                        pre = 0;
    unsigned long long         cur = 0;
    vector<int>                signal;
    vector<unsigned long long> value;
    for (int i = 0; i < n; i++) {
        i64 temp;
        cin >> temp;
        if ((temp > 0 && pre > 0) || (temp < 0 && pre < 0)) {
            cur += abs(temp);
        } else {
            value.emplace_back(cur);
            signal.emplace_back(pre);
            if (temp < 0) {
                pre = -1;
            } else {
                pre = 1;
            }
            cur = abs(temp);
        }
    }
    value.emplace_back(cur);
    signal.emplace_back(pre);
    unsigned long long ans = 0;
    i64                l = 1, r = (i64)signal.size() - 1LL;
    if (signal[l] == 1) {
        ans += value[l];
        l++;
    }
    if (signal[r] == -1) {
        ans += value[r];
        r--;
    }
    l++;
    r--;
    int         L = l, R = r;
    vector<i64> prefix(1, 0);
    i64         prefixval = 0;
    while (L <= r + 1) {
        prefixval += value[L];
        prefix.emplace_back(prefixval);
        L += 2;
    }
    prefixval = 0;
    vector<i64> suffix(1, 0);
    while (l - 1 <= R) {
        prefixval += value[R];
        suffix.emplace_back(prefixval);
        R -= 2;
    }
    i64 maxval = 0;
    for (int i = 0; i < prefix.size(); i++) {
        maxval = max(maxval, prefix[i] + suffix[prefix.size() - i - 1]);
    }
    cout << ans + maxval << '\n';
}

signed main(int argc, char** argv)
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

// -+-+-+