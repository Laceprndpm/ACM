#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

// 二分长度？二分距离？二分距离，且有大到小贪心？
// 先染前面全部的，随后开始尝试撤销shift键，如果撤销的
// 有几个状态？我目前在第idx个区间，place位置，我按过几次shift，每次区间多长。
void solve()

{
    int n, leng;
    cin >> n >> leng;
    vector<int> left(n + 1);
    vector<int> right(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> left[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> right[i];
    }

    int cntShift = 0;
    int place    = -1;
    int last     = -2;
    int idx;
    int cnt1 = 0;
    for (idx = 1; idx <= n; idx++) {
        int curlen     = right[idx] - left[idx] + 1;
        int isContinue = true;

        if (left[idx] != last + 1) {
            cntShift++;
            isContinue = false;
        }

        if (leng <= curlen) {
            place = left[idx] + leng - 1;
            break;
        } else {
            leng -= curlen;
            last = right[idx];
        }

        if (!isContinue) {
            if (curlen == 1) {
                cnt1++;
            }
        }
    }
    int curplace = place;
    if (place == -1) {  // 跑完了n个lr还没找到一个满足的地方
        cout << -1 << '\n';
        return;
    }
    int makeup    = 0;
    int maxmakeup = 0;
    while (cnt1--) {
        for (int i = 0; i < 2; i++) {
            place++;
            if (right[idx] >= place && left[idx] <= place) {
                makeup++;
            }
            if (place > right[idx] && idx < n) {
                idx++;
                if (left[idx] != right[idx - 1] + 1) {
                    makeup -= 2;
                }
            }
        }
        makeup--;
        maxmakeup = max(maxmakeup, makeup);
    }
    cout << curplace + 2 * cntShift - makeup << '\n';
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
