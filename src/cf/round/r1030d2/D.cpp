#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

void solve()
{
    i64 n;
    i64 k;
    cin >> n >> k;
    vector<i64> pos(n);
    for (i64& i : pos) {
        cin >> i;
    }
    vector<i64> delay(n);
    for (i64& i : delay) {
        cin >> i;
    }
    vector<array<int, 2>> ok(n);
    // 从后往前枚举
    // 假如我已经预处理完了踏上所有红绿灯红灯时的情况
    // 那么每次我只需要找到当前模类对应的红灯，取第一个就是目标
    // 令所有红灯计算当前坐标+delay % K
    //
    // 那么如何预处理出红灯呢？
    // 从前往后，第一个红灯肯定可以逃掉，同时记录一个map，为reteat[i]->int为ok
    // 第二个看能不能踩上第一个，踩上后就得往前，可以先存一个map，记录它的模类，即forward[i]->vector
    // 之后所有红灯枚举时先看看能不能被前面的踩，踩了后如果刚刚好碰上forward了。。。
    // 或者还是dfs，判断是否为环，这个可以
    //
    // map[i] i = postion - delay，然后存vector，来帮助二分
    //
    //
    //
    map<i64, vector<i64>> forward_mp;
    map<i64, vector<i64>> retreat_mp;
    for (int i = 0; i < n; i++) {
        u64 idx = pos[i] + k - delay[i];
        idx %= k;
        forward_mp[idx].emplace_back(pos[i]);
    }
    for (int i = 0; i < n; i++) {
        i64 idx = pos[i] + delay[i];
        idx %= k;
        retreat_mp[idx].emplace_back(pos[i]);
    }
    set<pair<i64, int>> vis;
    auto dfs = [&](auto&& self, i64 cur_idx, int direct) -> int {  // 0 表示正在向前 1 表示正在向后
        if (vis.count({cur_idx, direct})) {
            return 2;
        } else {
            vis.insert({cur_idx, direct});
        }
        if (ok[cur_idx][direct]) {
            return ok[cur_idx][direct];
        }
        if (direct == 1) {
            i64         cur_pos = (pos[cur_idx] + k - delay[cur_idx]) % k;
            const auto& vec     = forward_mp[cur_pos];
            i64         nxt     = upper_bound(all(vec), pos[cur_idx]) - bg(vec);
            if (nxt >= sz(vec)) {
                return ok[cur_idx][direct] = 1;
            }
            i64 nxt_idx                = lower_bound(all(pos), vec[nxt]) - bg(pos);
            return ok[cur_idx][direct] = self(self, nxt_idx, 0);
        } else {
            i64         idx = (pos[cur_idx] + delay[cur_idx]) % k;
            const auto& vec = retreat_mp[idx];
            i64         nxt = lower_bound(all(vec), pos[cur_idx]) - bg(vec) - 1;
            if (nxt < 0) {
                return ok[cur_idx][direct] = 1;
            }
            i64 nxt_idx                = lower_bound(all(pos), vec[nxt]) - bg(pos);
            return ok[cur_idx][direct] = self(self, nxt_idx, 1);
        }
    };
    for (int i = 0; i < n; i++) {
        vis.clear();
        dfs(dfs, i, 0);
    }
    int q;
    cin >> q;
    while (q--) {
        i64 ai;
        cin >> ai;
        const auto& vec = forward_mp[ai % k];
        if (vec.empty()) {
            cout << "YES\n";
            continue;
        } else {
            auto it = lower_bound(all(vec), ai);
            if (it == vec.end()) {
                cout << "YES\n";
                continue;
            } else {
                int idx = lower_bound(all(pos), *it) - bg(pos);
                if (ok[idx][0] == 1) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
                continue;
            }
        }
    }
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */