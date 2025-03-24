#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

inline int lowbit(int x)
{
    return x & -x;
}

void update(vector<int> &bit, int x, int v)
{
    for (int i = x; i < bit.size(); i += lowbit(i)) {
        bit[i] += v;
    }
}

int query(vector<int> &bit, int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += bit[i];
    }
    return res;
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 01 11 00
    // 11 11 11 11 0 0 0 0 0 0 1 0 1 0 1 0 0  1
    // 哪些情况下1必胜。。。当且仅当cnt1 * 3 <= cnt0?
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> cnt(n + 1);
    int         tempcnt0 = 0;
    int         tempcnt1 = 0;
    // array<int, 3>       cntMOD({1, 0, 0});
    i64 ans = 0;
    // 保证l-r间cnt0 - cnt1 * 3 == 2 MOD 3
    // 且cnt0 - cnt1 * 3 >= -1
    vector<int> bitTree(n * 8 + 4);
    update(bitTree, 4 * n + 4, 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            tempcnt0++;
        } else {
            tempcnt1++;
        }
        int cur    = tempcnt0 - tempcnt1 * 3;
        int remain = cur + 4 * n + 4;
        ans += query(bitTree, remain - 2);
        // cur1 - cur2 >= 2，代表按照最优策略，依然剩俩0
        ans += query(bitTree, remain + 1) - query(bitTree, remain);
        // 特殊情况，即01及其衍生型，此时cue1 - cur2 == -1
        update(bitTree, remain, 1);
    }
    cout << ans;
    return 0;
}