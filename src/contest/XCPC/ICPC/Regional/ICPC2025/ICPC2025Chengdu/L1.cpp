#include <array>
#include <iostream>
#include <memory>
#include <vector>
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
    vector<array<int, 2>> cnt0(n + 1);

    auto getsz = [&](auto self, int u, int fa) -> void {
        siz[u] = 1;  // every vertex has itself in its subtree
        if (arr[u] == 0) {
            cnt0[u][0]++;
        }
        if (brr[u] == 0) {
            cnt0[u][1]++;
        }
        for (auto v : adj[u])
            if (v != fa) {
                self(self, v, u);
                siz[u] += siz[v];  // add size of child u to its parent(v)
                cnt0[u][0] += cnt0[v][0];
                cnt0[u][1] += cnt0[v][1];
            }
    };
    getsz(getsz, 1, 0);
    vector<int>                     ans(n + 1);
    vector<unique_ptr<vector<int>>> vec(n + 1);
    vector<int>                     cnt(n + 1);
    int                             a = 0, b = 0;

    auto update = [&](int val) {
        if (cnt[abs(val)] < 0) {
            b -= cnt[abs(val)];
        } else {
            a -= cnt[abs(val)];
        }
        if (val < 0) {
            cnt[-val]--;
        } else if (val > 0) {
            cnt[val]++;
        }
        if (cnt[abs(val)] < 0) {
            b += cnt[abs(val)];
        } else {
            a += cnt[abs(val)];
        }
    };
    auto dfs = [&](auto&& self, int u, int p, bool keep) -> void {
        int mx = -1, bigChild = -1;
        for (auto v : adj[u])
            if (v != p && siz[v] > mx) mx = siz[v], bigChild = v;
        for (auto v : adj[u])
            if (v != p && v != bigChild) self(self, v, u, 0);
        if (bigChild != -1)
            self(self, bigChild, u, 1), vec[u] = std::move(vec[bigChild]);
        else
            vec[u] = make_unique<vector<int>>();
        vec[u]->push_back(u);
        update(arr[u]);
        update(-brr[u]);
        for (auto v : adj[u])
            if (v != p && v != bigChild)
                for (auto x : *vec[v]) {
                    update(arr[x]);
                    update(-brr[x]);
                    vec[u]->push_back(x);
                }
        // now cnt[c] is the number of vertices in subtree of vertex v that has color c.
        //  note that in this step *vec[v] contains all of the subtree of vertex v.
        if (cnt0[u][1] >= a && cnt0[u][0] >= b) {
            ans[u] = 1;
        }
        if (keep == 0)
            for (auto x : *vec[u]) {
                update(-arr[x]);
                update(brr[x]);
            }
    };
    dfs(dfs, 1, 0, 0);
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