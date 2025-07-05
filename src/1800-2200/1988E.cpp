#include <algorithm>
#include <array>
#include <iostream>
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
    vector<i64> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    CartesianTree<i64> ctree(arr);
    auto               child = ctree.child;
    int                root  = ctree.treeRoot;
    vector<i64>        tree_size(n + 1), val(n + 1);
    i64                sum  = 0;
    auto               dfs1 = [&](this auto&& dfs1, int x) -> void {
        tree_size[x] = 1;
        for (int i = 0; i < 2; i++) {
            if (child[x][i] == 0) continue;
            dfs1(child[x][i]);
            tree_size[x] += tree_size[child[x][i]];
        }
        val[x] = (tree_size[child[x][0]] + 1ll) * (tree_size[child[x][1]] + 1ll) * arr[x];
        sum += val[x];
    };
    dfs1(root);
    vector<i64> ans(n + 1);
    auto        dfs2 = [&](this auto&& dfs2, int x, i64 delta) -> void {
        i64                   v = sum - val[x] - delta;
        vector<array<i64, 2>> lr, rl;
        int                   y = child[x][0];
        while (y) {
            v -= val[y];
            lr.push_back({y, 0});
            y = child[y][1];
        }
        y = child[x][1];
        while (y) {
            v -= val[y];
            rl.push_back({y, 1});
            y = child[y][0];
        }
        vector<array<i64, 2>> res(lr.size() + rl.size());
        merge(lr.begin(), lr.end(), rl.begin(), rl.end(), res.begin(), [&](decltype(lr[0]) x, auto y) -> bool {
            return arr[x[0]] < arr[y[0]];
        });
        i64 cursz = 0;
        for (int i = (int)res.size() - 1; i >= 0; i--) {
            int p = res[i][0], q = res[i][1];
            // cout << "I:" << i << ' ' << cursz << '\n';
            v += (cursz + 1ll) * (tree_size[child[p][q]] + 1ll) * arr[p];
            cursz += tree_size[child[p][q]] + 1ll;
        }
        ans[x] = v;

        for (int i = 0; i < 2; i++)
            if (child[x][i]) dfs2(child[x][i], delta + 1ll * (tree_size[child[x][i ^ 1]] + 1) * arr[x]);
    };
    dfs2(root, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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