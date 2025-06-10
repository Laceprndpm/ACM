#include <bits/stdc++.h>
using namespace std;
using LL           = long long;
using PII          = pair<int, int>;
constexpr int MAXN = 2e5 + 5;
int           ai_input[MAXN];
int           n;
int           ans = INT32_MIN;

void dc(int l, int r)
{
    if (l == r) {
        ans = max(ans, ai_input[l]);
        return;
    }
    int mid = (r - l) / 2 + l;
    dc(l, mid);
    dc(mid + 1, r);
    int pre = INT32_MIN, suf = INT32_MIN;
    for (int i = mid, j = 0; i >= l; i--) {
        j += ai_input[i];
        pre = max(pre, j);
    }
    for (int i = mid + 1, j = 0; i <= r; i++) {
        j += ai_input[i];
        suf = max(suf, j);
    }
    ans = max(ans, pre + suf);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> ai_input[i];
    }
    dc(1, n);
    cout << ans;
    return 0;
}