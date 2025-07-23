#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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
#define len(x)  int(x.size())
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

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

/**
 *@brief 笛卡尔树
 */

template <class T>
struct CartesianTree {
    int                        n;
    vector<int>                stk;
    vector<std::array<int, 2>> child;
    vector<T>                  data;
    int                        treeRoot;

public:
    // 1-idx
    CartesianTree(vector<T>&& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(std::move(_init))
    {
        init();
    }

    CartesianTree(const vector<T>& _init) : n(_init.size() - 1), stk(n + 1), child(n + 1), data(_init)
    {
        init();
    }

    void init() noexcept
    {
        // stk 维护笛卡尔树中节点对应到序列中的下标
        int top = 0;
        for (int i = 1; i <= n; i++) {
            int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
            while (k > 0 && data[stk[k]] > data[i])
                k--;                                // 维护右链上的节点
            if (k) child[stk[k]][1] = i;            // 栈顶元素.右儿子 := 当前元素
            if (k < top) child[i][0] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
            stk[++k] = i;                           // 当前元素入栈
            top      = k;
        }
        treeRoot = stk[1];
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    CartesianTree<int> cat(arr);
    const auto&        child = cat.child;
    int                rt    = cat.treeRoot;
    vector<int>        size_tree(n + 1);
    i64                ans = 0;
    vector<i64>        val_tree(n + 1);

    auto dfs1 = [&](this auto&& dfs1, int u) -> void {
        if (!u) return;
        size_tree[u] = 1;
        for (int i = 0; i < 2; i++) {
            dfs1(child[u][i]);
            size_tree[u] += size_tree[child[u][i]];
        }
        val_tree[u] = ((size_tree[child[u][0]] + 1ll) * (size_tree[child[u][1]] + 1ll) * arr[u]);
        ans += val_tree[u];
    };
    dfs1(rt);

    vector<i64> final_ans(n + 1);
    const i64   orgin_total = ans;

    auto dfs2 = [&](this auto&& dfs2, int u, i64 delta) -> void {
        if (!u) return;
        i64                   cur_val = orgin_total - val_tree[u] - delta;
        vector<array<int, 2>> left_tree;
        vector<array<int, 2>> right_tree;
        int                   v;
        v = child[u][0];
        for (; v; v = child[v][1]) {
            cur_val -= val_tree[v];
            left_tree.pb({v, 0});
        }
        v = child[u][1];
        for (; v; v = child[v][0]) {
            cur_val -= val_tree[v];
            right_tree.pb({v, 1});
        }
        vector<array<int, 2>> remain_tree(sz(left_tree) + sz(right_tree));
        merge(all(left_tree), all(right_tree), bg(remain_tree), [&](const auto& a, const auto& b) {
            return arr[a[0]] < arr[b[0]];
        });
        reverse(all(remain_tree));
        i64 cursz = 0;
        for (const auto& [u, sub] : remain_tree) {
            cur_val += (cursz + 1ll) * arr[u] * (size_tree[child[u][sub]] + 1ll);
            cursz += size_tree[child[u][sub]] + 1;
        }
        final_ans[u] = cur_val;
        for (int i = 0; i < 2; i++) {
            dfs2(child[u][i], delta + (size_tree[child[u][!i]] + 1ll) * arr[u]);
        }
    };
    dfs2(rt, 0);
    for (int i = 1; i <= n; i++) {
        cout << final_ans[i] << ' ';
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