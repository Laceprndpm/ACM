#include <array>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    vector<int> brr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> brr[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<int>           siz(n + 1);
    vector<array<int, 2>> ab(n + 1);
    auto                  merge = [&](int u, map<int, int>& a, map<int, int>& b) {
        for (auto [i1, i2] : b) {
            int val = a[i1];
            if (val > 0) {
                ab[u][0] -= val;
            } else {
                ab[u][1] -= -val;
            }
            val = a[i1] += i2;
            if (a[i1] == 0) {
                a.extract(i1);
            }
            if (val > 0) {
                ab[u][0] += val;
            } else {
                ab[u][1] += -val;
            }
        }
    };
    vector<array<int, 2>> cnt0(n + 1);
    vector<int>           ans(n + 1);

    auto dfs = [&](auto&& self, int u, int fa) -> map<int, int> {
        siz[u] = 1;
        vector<pair<int, map<int, int>>> candi;
        for (int v : adj[u]) {
            if (v == fa) continue;
            candi.pb({v, std::move(self(self, v, u))});
            cnt0[u][0] += cnt0[v][0];
            cnt0[u][1] += cnt0[v][1];
            siz[u] += siz[v];
        }
        sort(all(candi), [&](const auto& a, const auto& b) { return siz[a.fi] > siz[b.fi]; });
        map<int, int> tmp;
        if (arr[u]) tmp[arr[u]]++;
        if (brr[u]) tmp[brr[u]]--;
        if (arr[u] == 0) {
            cnt0[u][0]++;
        }
        if (brr[u] == 0) {
            cnt0[u][1]++;
        }
        if (siz[u] == 1) {
            for (auto [_, v] : tmp) {
                if (v > 0) {
                    ab[u][0]++;
                } else if (v < 0) {
                    ab[u][1]++;
                }
            }
            if (cnt0[u][0] >= ab[u][1] && cnt0[u][1] >= ab[u][0]) {
                ans[u] = 1;
            }
            return std::move(tmp);
        }
        ab[u] = ab[candi[0].fi];
        for (int i = 1; i < candi.size(); i++) {
            merge(u, candi[0].se, candi[i].se);
        }
        merge(u, candi[0].se, tmp);
        if (cnt0[u][0] >= ab[u][1] && cnt0[u][1] >= ab[u][0]) {
            ans[u] = 1;
        }
        return std::move(candi[0].se);
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i];
    }
    cout << '\n';
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