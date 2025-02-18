#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
array<int, (int)2e5> arrInput;

void solve()
{
    int n;
    cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> arrInput[i];
        cnt[arrInput[i]]++;
    }
    int l    = -1;
    int r    = -1;
    int curL = 0;
    int maxL = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[arrInput[i]] == 1) {
            curL++;
            if (curL > maxL) {
                r    = i + 1;
                l    = i - curL + 2;
                maxL = curL;
            }
        } else {
            curL = 0;
        }
    }
    if (r == -1) {
        cout << 0 << '\n';
        return;
    } else {
        cout << l << ' ' << r << '\n';
    }
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

-+